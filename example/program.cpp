#include "abc/program/program.h"

#include <vector>
#include <string>
#include <algorithm>

int main(int argc, char** argv) {


	std::vector<std::string> strs;
	strs.push_back("aaa");
	strs.push_back("bbb");
	strs.push_back("ccc");

	std::find(strs.begin(), strs.end(), "bbb");

	abc::Program program;
	return program.run();

}

