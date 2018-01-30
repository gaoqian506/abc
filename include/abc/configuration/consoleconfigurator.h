#ifndef __ABC_CONFIGURATION_CONSOLE_CONFIGURATOR_HEADER__
#define __ABC_CONFIGURATION_CONSOLE_CONFIGURATOR_HEADER__

#include "configurator.h"

#include <string>
#include <vector>


using namespace std;

namespace abc {


class ConsoleConfigurator : public Configurator {

public:

	ConsoleConfigurator(shared_ptr<Configuration> configuration) 
		: Configurator(configuration) {}

	void parseFile(const std::string& name);

protected:

	// inherited from Asynchronous
	virtual void begin(void* param);

	// execute a command when user commit
	void exec(string& command);

	// parse the command into target and args
	shared_ptr<Configuration> parse(string& command, vector<string>& args);

	// set the args to target
	bool set(shared_ptr<Configuration>& configuration, const vector<string>& args);

};



} // namespace abc
#endif // __ABC_CONFIGURATION_CONFIGURATOR_HEADER__

