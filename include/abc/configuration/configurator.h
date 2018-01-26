#ifndef __ABC_CONFIGURATION_CONFIGURATOR_HEADER__
#define __ABC_CONFIGURATION_CONFIGURATOR_HEADER__

#include "configurable.h"

namespace abc {


class Configurator {

public:
	enum Type { 
		None = 0,
		Console = 1 << 0, 
		Socket = 1 << 1, 
		Html = 1 << 2, 
		Last = 1 << 3 
	};

	static Configurator* factory(Type type);
	static void asyncBegin(Configurator* configurator, 
		Configurable* configurable);
	void join() {}

	virtual void begin(Configurable* configurable) { }
};



} // namespace abc
#endif // __ABC_CONFIGURATION_CONFIGURATOR_HEADER__

