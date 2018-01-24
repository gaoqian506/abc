#include "abc/launcher/launcher.h"
#include "abc/learning/deep/raytracingprogram.h"


int main(int argc, char** argv) {

	abc::RaytracingProgram program(argc, argv);
	return abc::Launcher::launch(&program, abc::CommandLine | abc::Socket | abc::Html);
}

