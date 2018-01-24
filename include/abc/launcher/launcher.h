#ifndef __ABC_LAUNCHER_LAUNCHER_HEADER__
#define __ABC_LAUNCHER_LAUNCHER_HEADER__

#include "abc/program/program.h"

namespace abc {
namespace launcher {



class Launcher {

public:
	enum Platform {
		None, CommandLine, Socket, Html, Qt
	};

	static int launch(Launcher* launcher);
	static int launch(abc::program::Program* program, int platform);

	static Launcher* factory(Platform platform);
	virtual int launch() = 0;

private:
	Program* program;

};



} // namespace launcher
} // namespace abc
#endif // __ABC_LAUNCHER_LAUNCHER_HEADER__

