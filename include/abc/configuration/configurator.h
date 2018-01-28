#ifndef __ABC_CONFIGURATION_CONFIGURATOR_HEADER__
#define __ABC_CONFIGURATION_CONFIGURATOR_HEADER__

#include "configurable.h"

#include <thread>         // std::thread
#include <assert.h>

namespace abc {


class Configurator {

public:

	Configurator() : thread_(0) { }
	enum Type { 
		None = 0,
		Console = 1 << 0, 
		Socket = 1 << 1, 
		Html = 1 << 2, 
		Last = 1 << 3 
	};

	static Configurator* factory(Type type);
	static void asyncBegin(Configurator* configurator, 
		Configurable* configurable);
	static void syncBegin(Configurator* configurator, 
		Configurable* configurable);
	inline void join() { 
		assert(thread_ != 0);
		thread_->join();
	}

	virtual void begin(Configurable* configurable) { }

protected:

	inline void setThread(std::thread* thread) { 
		assert(thread_ == 0);
		thread_ = thread;
	}

	std::thread* thread_;
};



} // namespace abc
#endif // __ABC_CONFIGURATION_CONFIGURATOR_HEADER__

