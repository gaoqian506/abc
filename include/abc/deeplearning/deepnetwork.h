#ifndef __ABC_DEEP_LEARNING_DEEP_NETWORK_HEADER__
#define __ABC_DEEP_LEARNING_DEEP_NETWORK_HEADER__

#include "caffe/net.hpp"

//#include <memory>
#include <opencv2/core/core.hpp>

//using namespace std;


namespace abc {

typedef float DType;

class DeepNetwork {

public:
	DeepNetwork();
	~DeepNetwork();
	void load(const std::string& net_file);
	void release();
	void setBlob(const cv::Mat& mat, const std::string& name);

	inline void forward() { caffe_net_->Forward(); }
	inline void backward() { caffe_net_->Backward(); }


private:
	caffe::Net<DType>* caffe_net_;


};


} // namespace abc
#endif // __ABC_DEEP_LEARNING_DEEP_NETWORK_HEADER__
