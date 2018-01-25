#ifndef __ABC_LEARNING_DEEP_PROGRAM_HEADER__
#define __ABC_LEARNING_DEEP_PROGRAM_HEADER__

#include "abc/program/program.h"
#include "abc/learning/deep/network.h"


namespace abc {

class DeepLearningProgram : public Program {

public:

	//DeepLearningProgram(int& argc, char**& argv);
	DeepLearningProgram();

	virtual void getInput(){ };
	virtual void getLabel(){ };

	/**
	* @brief start method deprecated from v1.0
	* use run
	*/
	virtual void start();
	/**
	* @brief end deprecated from v1.0
	*/
	virtual void end();

	virtual void run();



protected:
	Network* network;

};


} // namespace abc
#endif // __ABC_LEARNING_DEEP_PROGRAM_HEADER__

