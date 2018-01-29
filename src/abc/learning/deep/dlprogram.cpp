#include "abc/learning/deep/dlprogram.h"


namespace abc {


DlProgram::DlProgram() {

	trainState_ = TrainStoped;
	testState_ = TestStoped;

	Configuration configTrain("train", Configuration::Select);
	configTrain.items().push_back("start");
	configTrain.items().push_back("pause");
	configTrain.items().push_back("resume");
	configTrain.items().push_back("stop");
	configuration()->addChild(configTrain);


	Configuration configTest("test", Configuration::Select);
	configTest.items().push_back("start");
	configTest.items().push_back("pause");
	configTest.items().push_back("resume");
	configTest.items().push_back("stop");
	configuration()->addChild(configTest);

}

bool DlProgram::configurationChanged(Configuration* configuration) {
	if (configuration->name() == "train") {
		if (configuration->text() == "start" && trainState_ == TrainStoped) {
			trainState_ = Training;
			DlProgram::ayncTrain(this);
		}
	}
	else 	if (configuration->name() == "test") {
		if (configuration->text() == "start" && testState_ == TestStoped) {
			testState_ = Testing;
			DlProgram::ayncTest(this);
		}
	}
	else {
		return false;
	}
}

void DlProgram::train() {


	while(trainState_ == Training) {
		trainStep();
	}

}

void DlProgram::test() {

	while(testState_ == Testing) {
		testStep();
	}

}

void DlProgram::asyncTrain(DlProgram* program) {
	std::thread thread(DlProgram::syncTrain, program);
}
void DlProgram::syncTrain(DlProgram* program) {
	program->train();
}
void DlProgram::asyncTest(DlProgram* program) {
	std::thread thread(DlProgram::syncTest, program);
}
void DlProgram::syncTest(DlProgram* program) {
	program->test();
}







};


