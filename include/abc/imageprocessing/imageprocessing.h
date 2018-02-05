#ifndef __ABC_IMAGE_PROCESSING_IMAGE_PROCESSING_HEADER__
#define __ABC_IMAGE_PROCESSING_IMAGE_PROCESSING_HEADER__

#include <opencv2/core/core.hpp>
#include <vector>
#include <string>

//using namespace std;

namespace abc {

class ImageProcessing {

public:

	// find images in dir
	static std::vector<std::string> find(const std::string& dir);

	// randomly select a image name to read
	static cv::Mat random_read(const std::vector<std::string>& names, int* selected_id = 0);
	

	// overlap object on background
	static cv::Mat overlap(cv::Mat& back, const cv::Mat& fore, float minScale = 0.8f, float maxScale = 3.0f);

	static cv::Mat resize(const cv::Mat m, int max_size);

	static cv::Mat convert(const cv::Mat m, int rtype, double alpha = 1, double beta = 0); 

	static void save(const std::string& name, const cv::Mat& image);

	static int parse_num(const std::string& str,int npos = 0,std::string parse_str = "._-");


private:

	static cv::RNG rng;

};




} // namespace abc
#endif // __ABC_IMAGE_PROCESSING_IMAGE_PROCESSING_HEADER__

