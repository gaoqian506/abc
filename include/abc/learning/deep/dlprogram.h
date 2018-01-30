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

	DlProgram();


	// inherited from Configurable
	virtual void configurationChanged(shared_ptr<Configuration> configuration);



protected:
	shared_ptr<Network> network_;
	State state_;

};


} // namespace abc
#endif // __ABC_LEARNING_DEEP_PROGRAM_HEADER__

