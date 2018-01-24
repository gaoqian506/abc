#include "abc/launcher/launcher.h"
#include "abc/learning/deep/program.h"


int main(int argc, char** argv) {

	abc::learning::deep::Program program(argc, argv);
	return abc::launcher::Launcher::launch(
	program, 
	abc::launcher::Launcher::CommandLine | 
	abc::launcher::Launcher::Socket | 
	abc::launcher::Launcher::Html);
}

