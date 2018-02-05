#include "abc/configuration/configurator.h"
#include "abc/configuration/consoleconfigurator.h"


namespace abc {

Configurator* Configurator::factory(Type type) {

	switch(type) {
		case Console:
			return new ConsoleConfigurator();
		default:
			return 0;
	}

}



} // namespace abc
