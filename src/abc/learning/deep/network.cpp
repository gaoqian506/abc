#include "abc/learning/deep/network.h"



namespace abc {




Network::Network(const std::string& ptfile) {

	caffenet_ = make_shared<caffe::Net<DType>>(ptfile, caffe::TRAIN);
}

void Network::setBlob(const cv::Mat& mat, const std::string& name) {

/*
	caffe::Blob<DType>* blob = caffenet_->blob_by_name(name).get();

	const vector< int > & shape = blob->shape();
	for (vector<int>::const_iterator itr = shape.begin(); itr != shape.end(); itr++) {
		std::cout << *itr << std::endl;
	}
*/
	//std::vector<int> shape2 = { 1, 2, 3, 4};
	//blob->Reshape(shape2);

	assert(mat.type() % 8 == CV_32F);
	caffe::Blob<DType>* blob = caffenet_->blob_by_name(name).get();
	assert(blob);
	std::vector<int> shape = { 1, mat.channels(), mat.rows, mat.cols };
	blob->Reshape(shape);

	unsigned int size = mat.step[0]*mat.rows;
	assert(blob->count()*sizeof(float) == size);
	memcpy(blob->mutable_cpu_data(), mat.data, size);

}




} // namespace abc

