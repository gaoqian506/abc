#ifndef __ABC_PROGRAM_PROGRAM_HEADER__
#define __ABC_PROGRAM_PROGRAM_HEADER__

#include "abc/configuration/configurable.h"


namespace abc {

class Program : public Configurable {

public:
	//Program(int& argc, char**& argv);

	/**
	* @brief deprecated from v1.0
	*/
	virtual void start();
	/**
	* @brief deprecated from v1.0
	*/
	virtual void end();

	virtual int run();

};


} // namespace abc
#endif // __ABC_PROGRAM_PROGRAM_HEADER__

