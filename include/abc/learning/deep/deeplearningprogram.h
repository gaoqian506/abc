#ifndef __ABC_LEARNING_DEEP_PROGRAM_HEADER__
#define __ABC_LEARNING_DEEP_PROGRAM_HEADER__

#include "abc/program/program.h"
#include "abc/learning/deep/network.h"


namespace abc {

class DeepLearningProgram : public Program {

public:

	//DeepLearningProgram(int& argc, char**& argv);
	DeepLearningProgram();

	virtual void getInput() = 0;
	virtual void getLabel() = 0;

	virtual void start();
	virtual void end();



protected:
	Network* network;

};


} // namespace abc
#endif // __ABC_LEARNING_DEEP_PROGRAM_HEADER__

