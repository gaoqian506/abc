#include "abc/configuration/consoleconfigurator.h"

#include <assert.h>
#include <string.h>		// cmpstr
#include <iostream>		// std::cin, std::cout
#include <algorithm>	// std::find


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
		printf(">>>");
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
		configurable_->configurationChanged(c);
	}

}

Configuration* ConsoleConfigurator::parse(char* command, std::vector<std::string>& args) {

	Configuration* current = root_;
	Configuration* temp;
	while(*command == ' ' || *command == '\t')
	{ command++; }

	char* space = strchr(command, ' ');
	if (space) { *space = 0; }

	char* period;
	while(current && (period = strchr(command, '.'))) {
		*period = 0;
		temp = current->child(command);
		if (!temp) {
			printf("Configuration:%s not found in %s.\n", command, current->name().c_str());
		}
		current = temp;
		command = period+1;
	}
	
	if (current) {
		temp = current->child(command);
		if (!temp) {
			printf("Configuration:%s not found in %s.\n", command, current->name().c_str());
		}
		current = temp;
	}


	if (current && space) {
		command = space+1;
		while(*command == ' ' || *command == '\t') 
		{ command++; }

		while(space = strchr(command, ' ' )) {
			*space = 0;
			args.push_back(command);
			command = space+1;
			while(*command == ' ' || *command == '\t')
			{ command++; }
		}

		if (*command) {
			args.push_back(command);
		}
	}
	
	return current;

}

bool ConsoleConfigurator::set(Configuration* configuration, const std::vector<std::string>& args) {

	bool ok = false;
	
	switch(configuration->type()) {
	case Configuration::Select:
		std::vector<std::string>& items = configuration->items();
		if (std::find(items.begin(), items.end(), args[0]) != items.end()) {
			configuration->text() = args[0];
			ok = true;
		}
		else {
			printf("Option %s not found in selection %s.\n", args[0].c_str(), configuration->name().c_str());
		}
		break;
	}
	return ok;
}


} // namespace abc
