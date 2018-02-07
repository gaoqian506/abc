#include "abc/program/program.h"
#include "abc/configuration/configurator.h"

#include <vector>
#include <memory>

namespace abc {

Program::Program() {
	set_name("program");
	configuration_->name() = "program";
}


int Program::start(int configurators/* = Configurator::Console*/) {


	for (int i = 1; i != Configurator::Last; i<<=1) {
		if (i & configurators) {
			Configurator* c = Configurator::factory((Configurator::Type)i);
			if (c) {
				c->add_configuration(this->configuration());
				//c->run();
				configurators_[(Configurator::Type)i] = c;				
			}

		}
	}

	bool ok = after_started();

	if (ok) {
		for (std::map<Configurator::Type, Configurator*>::iterator itr 
			= configurators_.begin(); itr != configurators_.end(); itr++) {
			itr->second->run();
		}

		for (std::map<Configurator::Type, Configurator*>::iterator itr 
			= configurators_.begin(); itr != configurators_.end(); itr++) {
			itr->second->join();
		}

	}

	for (std::map<Configurator::Type, Configurator*>::iterator itr 
		= configurators_.begin(); itr != configurators_.end(); itr++) {
		delete itr->second;
	}

	configurators_.clear();
	return 0;

}




} // namespace abc
