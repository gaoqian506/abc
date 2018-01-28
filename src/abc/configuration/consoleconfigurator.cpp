#include "abc/configuration/consoleconfigurator.h"

#include <assert.h>
#include <string.h>

namespace abc {

ConsoleConfigurator::ConsoleConfigurator() {

	configurable_ = 0;
	root_ = 0;
	current_ = 0;
	exit_ = false;
	command_ = (char*)malloc(MAX_COMMAND_LENGTH*sizeof(char));
	word_ = command_;

}

void ConsoleConfigurator::begin(Configurable* configurable) {

	init(configurable);
	printCommand();
	char ch;
	while(ch = getchar()) {
		appendChar(ch);
		if (exit) { break; }
	}


}

void ConsoleConfigurator::init(Configurable* configurable) {
	configurable_ = configurable;
	root_ = configurable->configuration();
	current_ = root_;
	exit_ = false;
	history_.clear();
	cursor_ = 0;
	word_ = command_;
	command_[cursor_] = 0;
}
void ConsoleConfigurator::printCommand() {
	printf("%s%s", ">>>", command_);
}

void ConsoleConfigurator::appendChar(const char& ch) {
	switch(ch) {
	case '\n':
		commit();
		break;
	case '\t':
		promot();
		break;
	case '.':
	case ' ':
		forward();
		break;
	case 27:
		moveup();
		break;
	case 28:
		movedown();
		break;
	default:
		putchar(ch);
		if (ch == '\b' && cursor_ > 0) {
			command_[--cursor_] = 0;
		}
		else {
			command_[cursor_++] = ch;
			command_[cursor_] = 0;
			assert(cursor_ <= MAX_COMMAND_LENGTH);
		}

	}
}


void ConsoleConfigurator::commit() {

	if (strcmp(command_, "exit") == 0) {
		exit_ = true;
		return;
	}
	if (current_ /*&& current->set(word_)*/) {
		//configurable->configurationChanged(current_);
	}

}
void ConsoleConfigurator::promot() {

	if (current_) {
		std::vector<std::string> candidates = match(current_, word_);
		if (candidates.size() == 1) { 
			//appendString(candidates[0]-word);
		}
		else if (candidates.size() > 1) {
			//list（candidates);
			//printCommand();
		}
	}

}

void ConsoleConfigurator::forward() {

	if (current_) {
		current_ = find(current_, word_);
	}

}
void ConsoleConfigurator::moveup() {

}
void ConsoleConfigurator::movedown() {

}

std::vector<std::string> ConsoleConfigurator::match(Configuration* con, std::string word) {
	return std::vector<std::string>();
}

Configuration* ConsoleConfigurator::find(Configuration* con, std::string word) {
	return 0;
}


} // namespace abc
