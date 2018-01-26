#include "abc/program/program.h"

#include <vector>

namespace abc {


int Program::run(int configurators/* = Configurator::Console*/) {

	std::vector<Configurator*> cs;

	for (int i = 1; i != Configurator::Last; i<<=1) {
		if (i & configurators) {
			Configurator* c = Configurator::factory((Configurator::Type)i);
			cs.push_back(c);
			Configurator::asyncBegin(c, this);
		}
	}

	for (std::vector<Configurator*>::iterator itr = cs.begin();
		itr != cs.end(); itr++) {
		(*itr)->join();
		delete (*itr);
	}

}



} // namespace abc
