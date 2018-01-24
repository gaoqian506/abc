#include "abc/learning/deep/raytracingprogram.h"

namespace abc {


RaytracingProgram::RaytracingProgram(int& argc, char**& argv) {

}

void RaytracingProgram::getInput() {

	// loadImage

}
void RaytracingProgram::getLabel() {
	// getLoss
	renderer->render();
	// calc loss
}



} // namespace abc
