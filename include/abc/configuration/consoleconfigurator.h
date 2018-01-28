#ifndef __ABC_CONFIGURATION_CONSOLE_CONFIGURATOR_HEADER__
#define __ABC_CONFIGURATION_CONSOLE_CONFIGURATOR_HEADER__

#include "configurator.h"

#define MAX_COMMAND_LENGTH 1024

namespace abc {


class ConsoleConfigurator : public Configurator {

public:

	ConsoleConfigurator();

	virtual void begin(Configurable* configurable);

protected:

	void init(Configurable* configurable);
	void printCommand();
	void appendChar(const char& ch);
	void commit();
	void promot();
	void forward();
	void moveup();
	void movedown();
	std::vector<std::string> match(Configuration* con, std::string word);
	Configuration* find(Configuration* con, std::string word);


	Configurable* configurable_;
	Configuration* root_;
	Configuration* current_;
	bool exit_;
	std::vector<char*> history_;
	char* command_;
	char* word_;
	int cursor_;
};



} // namespace abc
#endif // __ABC_CONFIGURATION_CONFIGURATOR_HEADER__

