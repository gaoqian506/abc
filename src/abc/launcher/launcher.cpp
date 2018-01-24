
#include "abc/launcher/launcher.h"


namespace abc {


int Launcher::launch(Launcher* launcher) {
	return launcher->launch();
}

int Launcher::launch(abc::Program* program, int platform) {
	return 0;
}

Launcher* Launcher::factory(LaunchPlatform platform) {
	return 0;
}



} // namespace abc
