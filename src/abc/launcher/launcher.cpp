
#include "abc/launcher/launcher.h"


namespace abc {
namespace Launcher {


int Launcher::launch(Launcher* launcher) {
	return launcher->launch();
}

int Launcher::launch(Program* program, Platform platform) {
	return 0;
}

Launcher* Launcher::factory(Platform platform) {
	return 0;
}



} // namespace Launcher
} // namespace abc
