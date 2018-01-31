#ifndef __ABC_LEARNING_DEEP_PROGRAM_HEADER__
#define __ABC_LEARNING_DEEP_PROGRAM_HEADER__

#include "abc/program/program.h"
#include "abc/learning/deep/network.h"

#include <memory>	// std::shared_ptr

using namespace std;

namespace abc {

class DlProgram : public Program {

public:
	enum State { Waiting = 0, Training, Testing };

	DlProgram(const string& netfile);


	// inherited from Configurable
	virtual void configurationChanged(shared_ptr<Configuration> configuration);



protected:

	// inherited from Asynchronous
	virtual void begin(void* param);

	// train step
	virtual void trainStep() {}

	// test step
	virtual void testStep() {}


	shared_ptr<Network> network_;
	State state_;

};


} // namespace abc
#endif // __ABC_LEARNING_DEEP_PROGRAM_HEADER__

