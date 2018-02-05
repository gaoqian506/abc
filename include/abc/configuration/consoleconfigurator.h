#ifndef __ABC_CONFIGURATION_CONSOLE__CONFIGURATOR_HEADER__
#define __ABC_CONFIGURATION_CONSOLE__CONFIGURATOR_HEADER__

#include "configurator.h"

// #include <string>
// #include <vector>


using namespace std;

namespace abc {


class ConsoleConfigurator : public Configurator {

public:

	ConsoleConfigurator();
	virtual ~ConsoleConfigurator();

	bool parse_file(const std::string& name);

	// execute a command when user commit
	void exec(const string& command);	

private:

	// inherited from Runner
	virtual bool step();



	// parse the command into target and args
	Configuration* parse(const string& command, string& name, string& param);

	void print_configuration(const Configuration* configuration, int depth = 0) const;
	void print_status(const Configuration* configuration, int depth = 0) const;
	void exit();


	// inherited from Configurable
	virtual void config(Configuration* configuration, const std::string& param);


};



} // namespace abc
#endif // __ABC_CONFIGURATION_CONSOLE__CONFIGURATOR_HEADER__

