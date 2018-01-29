#ifndef __ABC_IMAGE_IMAGE_HEADER__
#define __ABC_IMAGE_IMAGE_HEADER__

#include <opencv2/core/core.hpp>
#include <vector>
#include <string>


namespace abc {

class Image {

public:

	//static cv::Mat read(const char* path);
	static std::vector<std::string> find(const std::string& dir);
	//static void save(const char* path, const cv::Mat& mat);
	static cv::Mat overlap(const cv::Mat& back, const cv::Mat& fore);


};


} // namespace abc
#endif // __ABC_IMAGE_IMAGE_HEADER__

