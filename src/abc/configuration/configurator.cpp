#include "abc/configuration/configurator.h"
#include "abc/configuration/consoleconfigurator.h"

namespace abc {

Configurator* Configurator::factory(Type type) {

	Configurator* product;
	switch(type) {
		case Console:
			product = new ConsoleConfigurator();
			break;
		default:
			product = 0;
	}
	return product;

}

void Configurator::asyncBegin(Configurator* configurator, 
		Configurable* configurable) {

	std::thread* thread = new std::thread(Configurator::syncBegin, configurator, configurable);

	configurator->setThread(thread);

}

void Configurator::syncBegin(Configurator* configurator, Configurable* configurable) {
	configurator->begin(configurable);
}



} // namespace abc
