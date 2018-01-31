#ifndef __ABC_IMAGE_IMAGE_HEADER__
#define __ABC_IMAGE_IMAGE_HEADER__

#include <opencv2/core/core.hpp>
#include <vector>
#include <string>

using namespace std;

namespace abc {

class Image {

public:

	// find images in dir
	static vector<string> find(const string& dir);

	// overlap object on background
	static cv::Mat overlap(cv::Mat& back, const cv::Mat& fore, float minScale = 0.8f, float maxScale = 3.0f);


};


} // namespace abc
#endif // __ABC_IMAGE_IMAGE_HEADER__

