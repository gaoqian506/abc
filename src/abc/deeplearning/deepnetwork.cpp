#include "abc/deeplearning/deepnetwork.h"



namespace abc {




DeepNetwork::DeepNetwork() : caffe_net_(0) {

}

DeepNetwork::~DeepNetwork() {
	release();
}

void DeepNetwork::load(const std::string& net_file) {
	release();
	caffe_net_ = new caffe::Net<DType>(net_file, caffe::TRAIN);
}

void DeepNetwork::release() {
	LOG(INFO) << "[DeepNetwork] Before release caffe net." << caffe_net_;
	if (caffe_net_) {
		delete caffe_net_;
		caffe_net_ = 0;
	}
	LOG(INFO) << "[DeepNetwork] After release caffe net.";
}

void DeepNetwork::setBlob(const cv::Mat& mat, const std::string& name) {

	LOG(INFO) << "[DeepNetwork] before set blob.";

	CHECK(mat.type() % 8 == CV_32F) << "[DeepNetwork] Need a 32F typeof mat when set blob.";

	caffe::Blob<DType>* blob = caffe_net_->blob_by_name(name).get();

	CHECK(blob) << "[DeepNetwork] Get blob \"" << name << "\" from caffe net failed.";

	std::vector<int> shape = { 1, mat.channels(), mat.rows, mat.cols };
	blob->Reshape(shape);

	unsigned int size = mat.step[0]*mat.rows;
	CHECK(blob) << "[DeepNetwork] Blob size not match image's length of data.";
	memcpy(blob->mutable_cpu_data(), mat.data, size);
	LOG(INFO) << "[DeepNetwork] after set blob.";
}

caffe::Blob<DType>* DeepNetwork::getBlob(const std::string& name){
	caffe::Blob<DType>* blob = caffe_net_->blob_by_name(name).get();
	LOG(INFO)<<blob->shape()[0]<<"  "<<blob->shape()[1]<<"  "<<blob->shape()[2]<<"  "<<blob->shape()[3];
	//std::vector<int> shape = { 1, mat.channels(), mat.rows, mat.cols };
	//blob->Reshape(shape);
	return blob;
}


} // namespace abc
