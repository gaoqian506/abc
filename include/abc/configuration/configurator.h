#ifndef __ABC_CONFIGURATION_CONFIGURATOR_HEADER__
#define __ABC_CONFIGURATION_CONFIGURATOR_HEADER__

#include "configurable.h"


namespace abc {


class Configurator : public Configurable {

public:

	Configurator(shared_ptr<Configuration> configuration) 
		: configuration_(configuration) {}
	enum Type { None = 0, Console = 1, Socket = 2, Html = 4, Last = 8 };

	static shared_ptr<Configurator> factory(Type type, shared_ptr<Configuration> configuration);


protected:
	shared_ptr<Configuration> configuration_;

};



} // namespace abc
#endif // __ABC_CONFIGURATION_CONFIGURATOR_HEADER__

