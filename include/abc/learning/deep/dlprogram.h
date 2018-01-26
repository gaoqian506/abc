#ifndef __ABC_LEARNING_DEEP_PROGRAM_HEADER__
#define __ABC_LEARNING_DEEP_PROGRAM_HEADER__

#include "abc/program/program.h"
#include "abc/learning/deep/network.h"


namespace abc {

class DlProgram : public Program {

public:

	enum TrainFlag { Start, Pause, Resume, Stop };



	DlProgram();
	void train(TrainFlag flag = Start);
	virtual void getInputAndLabel(
		std::shared_ptr<caffe::Blob<DType>>& input, 
		std::shared_ptr<caffe::Blob<DType>>& label
	){ };

	virtual bool configurationChanged(Configuration* configuration);

	/**
	* @brief deprecated from v1.1.0
	*/
	virtual void getInput(){ };
	virtual void getLabel(){ };


protected:
	Network* network;

};


} // namespace abc
#endif // __ABC_LEARNING_DEEP_PROGRAM_HEADER__

