#ifndef __ABC_CONFIGURATION_CONFIGURATOR_HEADER__
#define __ABC_CONFIGURATION_CONFIGURATOR_HEADER__

#include "configurable.h"
#include "configuration.h"
#include "abc/asynchronous/runner.h"


namespace abc {


class Configurator : public Runner {

public:
	enum Type { None = 0, Console = 1, Last = 2 };

	virtual ~Configurator() {}

	static Configurator* factory(Type type);
	inline void add_configuration(Configuration* configuration) {
		configuration_->add_child(configuration);
	}


protected:
	// have declered in Configurable.
	//Configuration* configuration_;

	/** @brief protected constructor, only can instantinate with factory or inherits. */
	Configurator() {};	


};



} // namespace abc
#endif // __ABC_CONFIGURATION_CONFIGURATOR_HEADER__

