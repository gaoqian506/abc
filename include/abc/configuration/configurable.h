#ifndef __ABC_CONFIGURATION_CONFIGURABLE_HEADER__
#define __ABC_CONFIGURATION_CONFIGURABLE_HEADER__

#include "configuration.h"
#include "abc/asynchronous/asynchronous.h"

using namespace std;

namespace abc {



class Configurable : public Asynchronous {

public:

	Configurable() {
		configuration_ = make_shared<Configuration>(this, "root", Configuration::Category);
	}

	inline shared_ptr<Configuration> getConfiguration() 
	{ return configuration_; }



	virtual void configurationChanged(shared_ptr<Configuration> configuration) {}


protected:

	shared_ptr<Configuration> configuration_;


};



} // namespace abc
#endif // __ABC_CONFIGURATION_CONFIGURABLE_HEADER__

