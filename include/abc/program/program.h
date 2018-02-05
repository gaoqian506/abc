#ifndef __ABC_PROGRAM_PROGRAM_HEADER__
#define __ABC_PROGRAM_PROGRAM_HEADER__

#include "abc/asynchronous/runner.h"
#include "abc/configuration/configurator.h"

#include <map> // std::map

namespace abc {

class Program : public Runner {

public:
	Program();
	virtual ~Program() {}

	int start(int configurators = Configurator::Console);

	/** @brief will be called just after started. */
	virtual bool after_started() { return true; }

protected:
	std::map<Configurator::Type, Configurator*> configurators_;

};


} // namespace abc
#endif // __ABC_PROGRAM_PROGRAM_HEADER__

