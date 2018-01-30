#include "abc/learning/deep/dlprogram.h"
#include "abc/image/image.h"
// #include "abc/learning/deep/converter.h"
#include "abc/configuration/consoleconfigurator.h"

// #include <opencv2/highgui/highgui.hpp>

class MarkDetectionProgram : public abc::DlProgram {

public:

	MarkDetectionProgram(int argc, char** argv) {

	}


};

int main(int argc, char** argv) {

	MarkDetectionProgram program(argc, argv);
	return program.run();

}
