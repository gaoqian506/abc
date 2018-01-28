#include "abc/configuration/consoleconfigurator.h"

#include <assert.h>
#include <string.h>		// cmpstr
#include <iostream>     // std::cin, std::cout


namespace abc {

ConsoleConfigurator::ConsoleConfigurator() {

	configurable_ = 0;
	root_ = 0;
	exit_ = false;

}

void ConsoleConfigurator::begin(Configurable* configurable) {

	configurable_ = configurable;
	root_ = configurable_->configuration();

	char command[1024];

	while(true) {
		std::cin.getline(command, 1024);
		exec(command);
		if (exit_) { break; }
	}
}

void ConsoleConfigurator::exec(char* command) {

	if (strcmp(command, "exit") == 0) {
		exit_ = true;
		return;
	}

	
	std::vector<std::string> args;
	Configuration* c = parse(command, args);
	if (c && set(c, args)) {
		//configurable->configurationChanged(c);
		printf("%s", ">>>");
	}

}

Configuration* ConsoleConfigurator::parse(char* command, std::vector<std::string>& args) {

	Configuration* current = root_;
	while(*command == ' ' || *command == '\t')
	{ command++; }

	char* space = strchr(command, ' ');
	if (space) { *space = 0; }

	char* period;
	while(period = strchr(command, '.')) {
		*period = 0;
		current = current->child(command);
		if (!current) { 
			printf("Configuration %s not found", command);
			break;;
		}
		command = period+1;
	}

	current = current ? current->child(command) : current;

	if (current && space) {
		command = space;
		while(*command == ' ' || *command == '\t') 
		{ command++; }

		while(space = strchr(command, ' ' )) {
			*space = 0;
			args->push_back(command);
			command = space;
			while(*command == ' ' || *command == '\t')
			{ command++; }
		}

		if (command) {
			args->push_back(command);
		}
	}

	return 0; 
}

bool ConsoleConfigurator::set(Configuration* configuration, std::vector<std::string>& args) {

	return false;
}


} // namespace abc
