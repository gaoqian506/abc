#ifndef __ABC_LEARNING_DEEP_NETWORK_HEADER__
#define __ABC_LEARNING_DEEP_NETWORK_HEADER__


#include "caffe/net.hpp"


namespace abc {

class Network {

public:

	void setInput();
	void setLabel();
	void forward();
	void backward();

protected:
	caffe::Net* caffenet;

};


} // namespace abc
#endif // __ABC_LEARNING_DEEP_NETWORK_HEADER__

