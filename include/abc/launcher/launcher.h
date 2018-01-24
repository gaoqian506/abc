#ifndef __ABC_LAUNCHER_LAUNCHER_HEADER__
#define __ABC_LAUNCHER_LAUNCHER_HEADER__

#include "abc/program/program.h"

namespace abc {

enum LaunchPlatform {
	None, CommandLine, Socket, Html, Qt
};


class Launcher {

public:


	static int launch(Launcher* launcher);
	static int launch(abc::Program* program, int platform);

	static Launcher* factory(LaunchPlatform platform);
	virtual int launch() = 0;

private:
	Program* program;

};



} // namespace abc
#endif // __ABC_LAUNCHER_LAUNCHER_HEADER__

