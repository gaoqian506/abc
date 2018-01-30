#ifndef __ABC_LEARNING_DEEP_NETWORK_HEADER__
#define __ABC_LEARNING_DEEP_NETWORK_HEADER__

#include "caffe/net.hpp"

#include <memory>

using namespace std;
typedef float DType;

namespace abc {

class Network {

public:

	Network(const std::string& ptfile);
	void setBlob(const cv::Mat& mat, const std::string& name);


protected:


	shared_ptr<caffe::Net<DType>> caffenet_;



};


} // namespace abc
#endif // __ABC_LEARNING_DEEP_NETWORK_HEADER__

