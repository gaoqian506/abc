#ifndef __ABC_PROGRAM_PROGRAM_HEADER__
#define __ABC_PROGRAM_PROGRAM_HEADER__

#include "abc/configuration/configurable.h"


namespace abc {

class Program : public Configurable {

public:
	//Program(int& argc, char**& argv);
	virtual void start() = 0;
	virtual void end() = 0;

};


} // namespace abc
#endif // __ABC_PROGRAM_PROGRAM_HEADER__

