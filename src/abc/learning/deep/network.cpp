#include "abc/learning/deep/network.h"



namespace abc {


Network::Network(const std::string& ptfile) {

	caffenet_ = new caffe::Net<DType>(ptfile, caffe::TRAIN);
}

void Network::setBlob(const cv::Mat& mat, const std::string& name) {

}

//void Network::setBlob(caffe::Blob<DType> blob, const std::string& name) {

//}

void Network::learn(
	std::shared_ptr<caffe::Blob<DType>> input, 
	std::shared_ptr<caffe::Blob<DType>> label) {
	void setInput(caffe::Net<DType>* caffenet, std::shared_ptr<caffe::Blob<DType>> input);

}

void Network::setInput(std::shared_ptr<caffe::Blob<DType>> input) {

	//caffenet->setInput(input);
}
void Network::setLabel(std::shared_ptr<caffe::Blob<DType>> label) {

}


/**
* @brief following four deprecated from v1.1.0
*/
void Network::setInput() {}
void Network::setLabel() {}
void Network::forward() {}
void Network::backward() {}






};

