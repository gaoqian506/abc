#include "abc/configuration/consoleconfigurator.h"

#include <iostream>		// std::cin, std::cout
#include <sstream>		// std::stringstream
#include <algorithm>	// std::find
#include <fstream>      // std::ifstream

namespace abc {

void ConsoleConfigurator::parseFile(const std::string& name) {

	ifstream file(name, ifstream::in);
	if (file.is_open()) {
		string command;
		while(std::getline(file, command)) {
			exec(command);
		}
	}
	else {
		cout << name << "not found." << endl;
	}

}

void ConsoleConfigurator::begin(void* param){

	string command;
	while(!exit_) {
		printf(">>>");
		getline(cin, command);
		exec(command);
	}
}

void ConsoleConfigurator::exec(string& command){

	if (command == "exit") {
		exit_ = true;
		return;
	}

	std::vector<std::string> args;
	shared_ptr<Configuration> c = parse(command, args);
	if (c && set(c, args)) {
		c->owner()->configurationChanged(c);
	}
}

shared_ptr<Configuration> ConsoleConfigurator::parse(string& command, vector<string>& args){


	shared_ptr<Configuration> current = configuration_;
	shared_ptr<Configuration> temp;

	command.erase(0, command.find_first_not_of(" \t"));
	command.erase(command.find_last_not_of(" \t")+1);

	string confPart = command.substr(0, command.find_first_of(" \t"));
	string argPart = command.substr(command.find_first_of(" \t")+1);

	stringstream confStream(confPart);
	stringstream argsStream(argPart);

	vector<string> confs;
	string item;
	while (getline(confStream, item, '.')) {
		confs.push_back(item);
	}

	while (getline(argsStream, item, '.')) {
		args.push_back(item);
	}

	for (vector<string>::iterator itr = confs.begin(); itr != confs.end(); itr++) {
		temp = current->child(*itr);
		if (!temp) {
			cout << *itr << "not found in " << current->name() << endl;
		}
		else {
			current = temp;
		}
	}

	return current;

}

bool ConsoleConfigurator::set(shared_ptr<Configuration>& configuration, const vector<string>& args){

	bool ok = false;
	vector<string>& items = configuration->items();

	switch(configuration->type()) {
	case Configuration::Select:
		if (args.size() > 0 && std::find(items.begin(), items.end(), args[0]) != items.end()) {
			configuration->text() = args[0];
			ok = true;
		}
		else {
			cout << args[0] << " not found in option " << configuration->name() << endl;
		}
		break;
	case Configuration::Text:
		if (args.size() < 1) {
			cout << "Need a text augrment for " << configuration->name() << endl;
		}
		else {
			configuration->text() = args[0];
			ok = true;
		}
		break;
	}
	return ok;
}


} // namespace abc
