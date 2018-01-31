#include "abc/program/program.h"

#include <vector>
#include <memory>
#include <glog/logging.h>

namespace abc {



int Program::run(int configurators/* = Configurator::Console*/) {

	std::vector<std::shared_ptr<Configurator>> cs;
	std::shared_ptr<Configuration> configuration = getConfiguration();

	for (int i = 1; i != Configurator::Last; i<<=1) {
		if (i & configurators) {
			std::shared_ptr<Configurator> c = 
				Configurator::factory((Configurator::Type)i, configuration);
			LOG(INFO) << "A Configurator(" << i << ") created.";
			c->asyncBegin();
			cs.push_back(c);
		}
	}

	for (std::vector<std::shared_ptr<Configurator>>::iterator itr = cs.begin();
		itr != cs.end(); itr++) {
		(*itr)->join();
	}

}




} // namespace abc
