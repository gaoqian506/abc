#ifndef __ABC_LEARNING_DEEP_PROGRAM_HEADER__
#define __ABC_LEARNING_DEEP_PROGRAM_HEADER__

#include "abc/program/program.h"
#include "abc/learning/deep/network.h"


namespace abc {

class DlProgram : public Program {

public:



	DlProgram();

	/**
	* @brief deprecated from v1.1.1
	*/
	enum TrainFlag { Start, Pause, Resume, Stop };


	enum TrainState { Training, TrainStoped };
	enum TestState { Testing, TestStoped };

	void train();
	void test();
	virtual void trainStep() {}
	virtual void testStep() {}

	static void asyncTrain(DlProgram* program);
	static void syncTrain(DlProgram* program);
	static void asyncTest(DlProgram* program);
	static void syncTest(DlProgram* program);


	virtual bool configurationChanged(Configuration* configuration);

	/**
	* @brief deprecated from v1.1.0
	*/
	virtual void getInput(){ };
	virtual void getLabel(){ };


protected:
	Network* network;
	TrainState trainState_;
	TestState testState_;

};


} // namespace abc
#endif // __ABC_LEARNING_DEEP_PROGRAM_HEADER__

