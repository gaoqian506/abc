#ifndef __ABC_CONFIGURATION_CONSOLE_CONFIGURATOR_HEADER__
#define __ABC_CONFIGURATION_CONSOLE_CONFIGURATOR_HEADER__

#include "configurator.h"

#define MAX_COMMAND_LENGTH 1024

namespace abc {


class ConsoleConfigurator : public Configurator {

public:

	ConsoleConfigurator();

	virtual void begin(Configurable* configurable);
	void begin(Configurable* configurable, const std::string& filename);

protected:

	void exec(char* command);
	Configuration* parse(char* command, std::vector<std::string>& args);

	bool set(Configuration* configuration, const std::vector<std::string>& args);

	Configurable* configurable_;
	Configuration* root_;
	bool exit_;

};



} // namespace abc
#endif // __ABC_CONFIGURATION_CONFIGURATOR_HEADER__

