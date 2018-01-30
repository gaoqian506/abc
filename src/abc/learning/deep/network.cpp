#include "abc/learning/deep/network.h"



namespace abc {




Network::Network(const std::string& ptfile) {

	caffenet_ = make_shared<caffe::Net<DType>>(ptfile, caffe::TRAIN);
}

void Network::setBlob(const cv::Mat& mat, const std::string& name) {

}




} // namespace abc

