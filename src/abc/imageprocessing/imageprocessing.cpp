#include "abc/imageprocessing/imageprocessing.h"


#include <dirent.h>
#include <sys/types.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

namespace abc {

cv::RNG ImageProcessing::rng = cv::RNG((unsigned)time(NULL));


std::vector<std::string> ImageProcessing::find(const std::string& directory) {

	std::vector<std::string> list;

	DIR *dir=NULL;
	struct dirent* pDir=NULL;
	dir=opendir(directory.c_str());
	if(dir == NULL)
		printf("Error! can't open this dir\n");
	else{
		while(1) {
			pDir = readdir(dir);
			if (pDir == NULL) break;
			if (pDir->d_type == DT_REG) {
				std::string filename = pDir->d_name;			
				int idx = filename.rfind('.');
				std::string exname = filename.substr(idx+1,filename.length());
				if(exname == "jpg" || exname =="png" || exname == "JPG" || exname =="PNG") {
					list.push_back(directory + "/" + pDir->d_name);
				}
			}
		}
	}
	closedir(dir);



	return list;
}


cv::Mat ImageProcessing::overlap(cv::Mat& back, const cv::Mat& fore, float minScale, float maxScale) {

	//cv::RNG rng((unsigned)time(NULL));
	//cv::RNG rng;

	int angle = rng.uniform(0, 360);
	double scale1 = rng.uniform(minScale, maxScale);//浮点随机数
	cv::Point2f center;
	cv::Mat foreCut;
	cv::Mat mask_cut;
	if(scale1*fore.cols <= fore.cols){
		center = cv::Point2f(fore.cols*0.5, fore.rows*0.5);
		fore.copyTo(foreCut);
		mask_cut = cv::Mat(fore.size(),CV_8U,cv::Scalar(255));
	}else{
		float distance = sqrtf(powf((scale1*fore.cols),2) + powf((scale1*fore.rows),2));
		int width = distance;
		int height = distance;
		center = cv::Point2f(width*0.5f,height*0.5f);
		int x1 = center.x-fore.cols*0.5;
		int y1 = center.y-fore.rows*0.5;
		foreCut = cv::Mat(height,width,fore.type(),cv::Scalar(0));
		fore.copyTo(foreCut.rowRange(y1,y1+fore.rows).colRange(x1,x1+fore.cols));
		mask_cut = cv::Mat(height,width,CV_8U,cv::Scalar(0));
		mask_cut.rowRange(y1,y1+fore.rows).colRange(x1,x1+fore.cols) = cv::Scalar(255);//输出图像验证正确
	}
	cv::Mat H = cv::getRotationMatrix2D(center,angle,scale1);
	cv::Mat out_warp;
	cv::warpAffine(foreCut,out_warp,H,cv::Size(foreCut.cols,foreCut.rows));
	cv::Mat mask_cut_warp;
	cv::warpAffine(mask_cut,mask_cut_warp,H,cv::Size(mask_cut.cols,mask_cut.rows));
	int x = rng.uniform(mask_cut_warp.cols*0.5, back.cols-mask_cut_warp.cols*0.5-1);
	int y = rng.uniform(mask_cut_warp.rows*0.5, back.rows-mask_cut_warp.rows*0.5-1);
	cv::Rect rect;
	rect.x = x-mask_cut_warp.cols*0.5;
	rect.y = y-mask_cut_warp.rows*0.5;
	rect.width = mask_cut_warp.cols;
	rect.height = mask_cut_warp.rows;
	cv::Mat mask = cv::Mat(back.size(),CV_8U,cv::Scalar(0));
	mask_cut_warp.copyTo(mask.rowRange(rect.y,rect.y+rect.height).colRange(rect.x, rect.x+rect.width));

	for(int y = rect.y; y < rect.y+rect.height; y++){
		cv::Vec3b* src = back.ptr<cv::Vec3b>(y);
		cv::Vec3b* obj = out_warp.ptr<cv::Vec3b>(y-rect.y);
		uchar* p_mask = mask.ptr<uchar>(y);
		for(int x = rect.x; x < rect.x+rect.width; x++){
			if(p_mask[x] == 255)
				src[x] = obj[x-rect.x];
		}
	}

	return mask;
}


cv::Mat ImageProcessing::random_read(const std::vector<std::string>& names, int* selected_id/* = 0*/) {

	cv::Mat image;
	if (names.size() > 0) {
		int id = rand() % names.size();
		const std::string& name = names[id];
		image = cv::imread(name);
		if (selected_id) { *selected_id = id; }
	}
	return image;

}

cv::Mat ImageProcessing::read(const std::string& name) {

	cv::Mat image = cv::imread(name);
	return image;
}

cv::Mat ImageProcessing::resize(const cv::Mat m, int max_size) {


	double scale[2] = { (double)max_size / m.cols, (double)max_size / m.rows };
	double mins = scale[0] < scale[1] ? scale[0] : scale[1];
	cv::Mat out;
	cv::resize(m, out, cv::Size(), mins, mins);

	return out;
}


cv::Mat ImageProcessing::convert(const cv::Mat m, int rtype, double alpha, double beta) {
	cv::Mat out;
	m.convertTo(out, rtype, 1.0/255.0);
	return out;
}

void ImageProcessing::save(const std::string& name, const cv::Mat& image) {
	cv::imwrite(name, image);
}


int ImageProcessing::parse_num(const std::string& str,int npos,std::string parse_str)
{
	std::string dst = "";
	int ridx1 = str.rfind('/');
	int ridx2 = str.rfind('.');
	if(ridx2 == -1)return -1;

	char c[1024];
	memset(c,0,sizeof(char)*1024);
	std::string strsub = str.substr(ridx1+1,ridx2-ridx1-1);
	strcpy(c,strsub.c_str());
	char* p = strtok(c,parse_str.c_str());
	int num_idx = -1;
	while (p)
	{
		std::string tokstr = p;
		bool bfind = true;
		for(int i = 0; i < tokstr.length(); i++){
			if(((int)tokstr.at(i)) < 48 || ((int)tokstr.at(i)) > 57){// 0 ~ 9
				bfind = false;
				break;
			}
		}
		if(bfind){
			num_idx++;
			if(num_idx == npos){
				dst = tokstr;
				break;
			}
		}
		p = strtok(NULL,parse_str.c_str());
	}

	if(dst == "")return -1;
	return atoi(dst.c_str());
}



};

