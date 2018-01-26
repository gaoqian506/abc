#ifndef __ABC_CONFIGURATION_CONSOLE_CONFIGURATOR_HEADER__
#define __ABC_CONFIGURATION_CONSOLE_CONFIGURATOR_HEADER__

#include "configurator.h"

namespace abc {


class ConsoleConfigurator : public Configurator {

public:

	virtual void begin(Configurable* configurable);

};



} // namespace abc
#endif // __ABC_CONFIGURATION_CONFIGURATOR_HEADER__

