#include "abc/image/image.h"


#include <dirent.h>
#include <sys/types.h>

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
				if(exname == "jpg" || exname =="png") {
					list.push_back(directory + "/" + pDir->d_name);
				}
			}
		}
	}
	closedir(dir);



	return list;
}


cv::Mat Image::overlap(const cv::Mat& back, const cv::Mat& fore) {
	return cv::Mat();
}



};

