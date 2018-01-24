
#include "abc/learning/deep/deeplearningprogram.h"

namespace abc {

//DeepLearningProgram::DeepLearningProgram(int& argc, char**& argv) {
	
//}

DeepLearningProgram::DeepLearningProgram() {
}

void DeepLearningProgram::start() {

	
	while(true) {
		getInput();
		network->setInput();
		getLabel();
		network->setLabel();
		network->forward();
		network->backward();
	}

}

void DeepLearningProgram::end() {
}

} // namespace abc
