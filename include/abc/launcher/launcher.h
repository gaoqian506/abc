#ifndef __ABC_LAUNCHER_LAUNCHER_HEADER__
#define __ABC_LAUNCHER_LAUNCHER_HEADER__


class Program;

namespace abc {
namespace Launcher {



class Launcher {

public:
	enum Platform {
		None, CommandLine, Socket, Html, Qt
	};

	static int launch(Launcher* launcher);
	static int launch(Program* program, Platform platform);
	static Launcher* factory(Platform platform);
	virtual int launch() = 0;

private:
	Program* program;

};



} // namespace Launcher
} // namespace abc
#endif // __ABC_LAUNCHER_LAUNCHER_HEADER__

