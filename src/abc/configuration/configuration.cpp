#include "abc/configuration/configuration.h"

namespace abc {


Configuration* Configuration::child(const char* name) {

	Configuration* child = 0;
	//if (type_ != Category) { return 0; }

	for (std::vector<Configuration>::iterator itr = children_.begin(); itr != children_.end(); itr++) {
		if (itr->name_ == name) { 
			child = &(*itr);
			break;
		}
	}
	return child;
}

} // namespace abc
