#ifndef __ABC_LEARNING_DEEP_NETWORK_HEADER__
#define __ABC_LEARNING_DEEP_NETWORK_HEADER__


#include "caffe/net.hpp"

typedef float DType;

namespace abc {

class Network {

public:

	void learn(
		std::shared_ptr<caffe::Blob<DType>> input, 
		std::shared_ptr<caffe::Blob<DType>> label);

	/**
	* @brief following four deprecated from v1.1.0
	*/
	void setInput();
	void setLabel();
	void forward();
	void backward();

protected:

	void setInput(std::shared_ptr<caffe::Blob<DType>> input);
	void setLabel(std::shared_ptr<caffe::Blob<DType>> label);

	caffe::Net<DType>* caffenet;


	
};


} // namespace abc
#endif // __ABC_LEARNING_DEEP_NETWORK_HEADER__

