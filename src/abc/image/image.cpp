#include "abc/image/image.h"


#include <dirent.h>
#include <sys/types.h>
#include <opencv2/imgproc/imgproc.hpp>

namespace abc {


std::vector<std::string> Image::find(const std::string& directory) {

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


cv::Mat Image::overlap(cv::Mat& back, const cv::Mat& fore, float minScale, float maxScale) {

	cv::RNG rng((unsigned)time(NULL));

	int angle = rng.uniform(0, 360);
	double scale1 = rng.uniform(minScale, maxScale);//浮点随机数
	cv::Point2f center;
	cv::Mat foreCut;
	cv::Mat mask_cut;
	if(scale1*fore.cols <= fore.cols){
		center = cv::Point2f(fore.cols*0.5, fore.rows*0.5);
		fore.copyTo(foreCut);
		mask_cut = cv::Mat(fore.size(),CV_8U,cv::Scalar(1));
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
		mask_cut.rowRange(y1,y1+fore.rows).colRange(x1,x1+fore.cols) = cv::Scalar(1);//输出图像验证正确
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
			if(p_mask[x] == 1)
				src[x] = obj[x-rect.x];
		}
	}

	return mask;
}


};

