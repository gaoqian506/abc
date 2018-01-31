#ifndef __ABC_LEARNING_DEEP_NETWORK_HEADER__
#define __ABC_LEARNING_DEEP_NETWORK_HEADER__

#include "caffe/net.hpp"

#include <memory>
#include <opencv2/core/core.hpp>

using namespace std;
typedef float DType;

namespace abc {

class Network {

public:

	Network(const std::string& ptfile);
	void setBlob(const cv::Mat& mat, const std::string& name);

	inline void forward() { caffenet_->Forward(); }
	inline void backward() { caffenet_->Backward(); }


protected:


	shared_ptr<caffe::Net<DType>> caffenet_;



};


} // namespace abc
#endif // __ABC_LEARNING_DEEP_NETWORK_HEADER__

