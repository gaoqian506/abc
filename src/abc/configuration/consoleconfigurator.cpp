#include "abc/configuration/consoleconfigurator.h"

#include <iostream>		// std::cin, std::cout
#include <sstream>		// std::stringstream
#include <algorithm>	// std::find
#include <fstream>      // std::ifstream

#include <glog/logging.h>

namespace abc {


ConsoleConfigurator::ConsoleConfigurator() {

	set_name("ConsoleConfigurator");
	configuration_->name() = "ConsoleConfigurator";
	Configuration* action_help = new Configuration(this, Configuration::Action, 
		"help", "", "print configuration infomation.");
	Configuration* action_status = new Configuration(this, Configuration::Action, 
		"status", "", "print configuration status.");;
	Configuration* action_exit = new Configuration(this, Configuration::Action, 
		"exit", "", "terminate for configurating.");;

	configuration_->add_child(action_help);
	configuration_->add_child(action_status);
	configuration_->add_child(action_exit);

	add_configuration_for_auto_release(action_help);
	add_configuration_for_auto_release(action_status);
	add_configuration_for_auto_release(action_exit);
	//add_configuration_for_auto_release(configuration_);

	configuration_->child("run")->mute() = true;
	configuration_->child("stop")->mute() = true;

	LOG(INFO) << name() << " Constructs with children count:" << configuration_->children_count();
	

}

ConsoleConfigurator::~ConsoleConfigurator() {
	LOG(INFO) << name() << " (ConsoleConfigurator)before destroy.";
	
	LOG(INFO) << name() << " (ConsoleConfigurator)after destroy.";
}

bool ConsoleConfigurator::parse_file(const std::string& name) {

	ifstream file(name, ifstream::in);
	if (file.is_open()) {
		string command;
		while(std::getline(file, command)) {
			exec(command);
		}
		return true;
	}
	else {
		LOG(INFO) << this->name() << ": " << name << "not found.";
		return false;
	}

}

bool ConsoleConfigurator::step() {

	std::string command;
	printf(">>>");
	getline(std::cin, command);
	exec(command);
	return true;

}

void ConsoleConfigurator::exec(const string& command) {

	std::string name, param;

	Configuration* configuration = parse(command, name, param);
	if (configuration && !configuration->mute() && configuration->owner()) {
		LOG(INFO) << this->name() << " before config command:" << command\
			<< ", owner:" << configuration->owner()->name();
		configuration->owner()->config(configuration, param);
		LOG(INFO) << this->name() << " after config command:" << command;
	}

}


Configuration* ConsoleConfigurator::parse(const string& command, string& name, string& param) {

	LOG(INFO) << this->name() << " before parsing command:" << command;
	std::string nospace = command;
	nospace.erase(0, nospace.find_first_not_of(" \t"));
	nospace.erase(nospace.find_last_not_of(" \t")+1);


	string conf_part = nospace.substr(0, nospace.find_first_of(" \t"));
	param = nospace.substr(nospace.find_first_of(" \t")+1);

 	// if no separator
	if (conf_part == param) { param = ""; }
	else { param.erase(0, param.find_first_not_of(" \t")); }

	stringstream conf_stream(conf_part);
	vector<string> conf_list;
	string item;
	while (getline(conf_stream, item, '.')) { conf_list.push_back(item); }

	Configuration* parrent = configuration_;
	Configuration* child = 0;
	for (vector<string>::iterator itr = conf_list.begin(); itr != conf_list.end(); itr++) {
		name = *itr;
		LOG(INFO) << this->name() << " find child configuration by name:" << name;
		child = parrent->child(name);
		if (!child) {
			cout << "Configuration " << name << " not found.\n";
			break;
		}
		LOG(INFO) << this->name() << " " << name << "'s owner:" << child->owner()->name();
		parrent = child;
		
	}

	LOG(INFO) << this->name() << " after parsing command:" << command;

	return child;

}

void ConsoleConfigurator::config(Configuration* configuration, const std::string& param) {

	assert(configuration);

	LOG(INFO) << name() << " will config:" << configuration->name();
	
	if (configuration->name() == "help") {
		print_configuration(configuration_);
	}
	else if (configuration->name() == "status") {
		print_status(configuration_);
	}
	else if (configuration->name() == "exit") {	stop();	}
	else {
		LOG(INFO) << this->name() << " before forward command.";
		Runner::config(configuration, param); 
		LOG(INFO) << this->name() << " after forward command.";
	}

}


void ConsoleConfigurator::print_configuration(const Configuration* configuration, int depth) const {

	// indent
	

	switch(configuration->type()) {
	case Configuration::Text:
		if (!configuration->mute()) {
			for (int d = 0; d < depth; ++d) { std::cout << "\t"; }
			std::cout << "[ Text ]" << configuration->name() << "==" \
			<< configuration->text() << "--" <<\
			configuration->description() << std::endl;			
		}
		break;
	case Configuration::Action:
		if (!configuration->mute()) {
			for (int d = 0; d < depth; ++d) { std::cout << "\t"; }
			std::cout << "[Action]" << configuration->name() << "--" \
			<< configuration->description() << std::endl;
		}
		break;
	case Configuration::Status:
		if (!configuration->mute()) {
			for (int d = 0; d < depth; ++d) { std::cout << "\t"; }
			std::cout << "[Status]" << configuration->name() << "==" \
			<< configuration->text() << "--" <<\
			configuration->description() << std::endl;
		}		
		break;
	case Configuration::Category:
		//std::cout << "\n";
		for (int d = 0; d < depth; ++d) { std::cout << "\t"; }
		std::cout << "{" << configuration->name() << "}\n";
		const std::vector<Configuration*>& children = configuration->children();
		for (std::vector<Configuration*>::const_iterator itr = children.begin(); 
			itr != children.end(); ++itr) {
			print_configuration(*itr, depth+1);
		}
		break;		
	}
}

void ConsoleConfigurator::print_status(const Configuration* configuration, int depth) const {

//Category = 0, Text, Action, Status
	// indent


	switch(configuration->type()) {
	case Configuration::Status:
		if (!configuration->mute()) {
			for (int d = 0; d < depth; ++d) { std::cout << "\t"; }
			std::cout << "[Status]" << configuration->name() << "==" \
			<< configuration->text() << "--" <<\
			configuration->description() << std::endl;
		}
		break;
	case Configuration::Category:
		//std::cout << "\n";
		for (int d = 0; d < depth; ++d) { std::cout << "\t"; }
		std::cout << "{" << configuration->name() << "}\n";
		const std::vector<Configuration*>& children = configuration->children();
		for (std::vector<Configuration*>::const_iterator itr = children.begin(); 
			itr != children.end(); ++itr) {
			print_status(*itr, depth+1);
		}
		break;		
	}
}

void ConsoleConfigurator::exit() {
	std::cout << "Exit action.\n";
}

/*

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

	LOG(INFO) << "Waiting console command...";

	string command;
	while(!exit_) {
		printf(">>>");
		getline(cin, command);
		exec(command);
	}

	LOG(INFO) << "Waiting console command exit.";
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

	while (getline(argsStream, item, ' ')) {
		args.push_back(item);
	}

	for (vector<string>::iterator itr = confs.begin(); itr != confs.end(); itr++) {
		temp = current->child(*itr);
		if (!temp) {
			cout << *itr << " not found in " << current->name() << endl;
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


*/

} // namespace abc
