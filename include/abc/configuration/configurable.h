#ifndef __ABC_CONFIGURATION_CONFIGURABLE_HEADER__
#define __ABC_CONFIGURATION_CONFIGURABLE_HEADER__

#include "configuration.h"

namespace abc {



class Configurable {

	//virtual const Configuration& getConfiguration() = 0;
public:

	Configurable() {
		configuration_ = new Configuration("root", Configuration::Category);
	}

	~Configurable() {
		delete configuration_;
	}

virtual bool configurationChanged(Configuration* configuration) {
	return false;
}

inline Configuration* configuration() { return configuration_; }
//inline Configuration& configuration() { return configuration_; }

protected:

	Configuration* configuration_;


};



} // namespace abc
#endif // __ABC_CONFIGURATION_CONFIGURABLE_HEADER__

