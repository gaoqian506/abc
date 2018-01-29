#include "abc/learning/deep/network.h"



namespace abc {



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

