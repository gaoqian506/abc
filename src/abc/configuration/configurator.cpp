#include "abc/configuration/configurator.h"
#include "abc/configuration/consoleconfigurator.h"

namespace abc {


shared_ptr<Configurator> Configurator::factory(Type type, shared_ptr<Configuration> configuration) {

	switch(type) {
		case Console:
			return make_shared<ConsoleConfigurator>(configuration);
		default:
			return shared_ptr<Configurator>();
	}

}



} // namespace abc
