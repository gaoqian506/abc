#ifndef __ABC_IMAGE_IMAGE_HEADER__
#define __ABC_IMAGE_IMAGE_HEADER__

#include <opencv2/core/core.hpp>
#include <vector>
#include <string>


namespace abc {

class Image {

public:

	static cv::Mat read(const char* path, random = false, int* index);
	static std::vector<std::string> find(const char* dir);
	static void save(const char* path, const cv::Mat& mat);


};


} // namespace abc
#endif // __ABC_IMAGE_IMAGE_HEADER__

