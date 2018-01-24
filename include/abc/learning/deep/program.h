#ifndef __ABC_LEARNING_DEEP_PROGRAM_HEADER__
#define __ABC_LEARNING_DEEP_PROGRAM_HEADER__

#include "abc/program/program.h"


namespace abc {
namespace learning {
namespace deep {

class Program : public abc::Program::Program {

public:
	//virtual const Configuration& getConfiguration() = 0;
	Program(int& argc, char** argv);
	virtual void start();
	virtual void end();

protected:
	

};


} // namespace deep
} // namespace learning
} // namespace abc
#endif // __ABC_LEARNING_DEEP_PROGRAM_HEADER__

