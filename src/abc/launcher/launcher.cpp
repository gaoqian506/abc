
#include "abc/launcher/launcher.h"


namespace abc {
namespace launcher {


int Launcher::launch(Launcher* launcher) {
	return launcher->launch();
}

int Launcher::launch(abc::program::Program* program, int platform) {
	return 0;
}

Launcher* Launcher::factory(Platform platform) {
	return 0;
}



} // namespace launcher
} // namespace abc
