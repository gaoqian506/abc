#include "abc/learning/deep/dlprogram.h"


namespace abc {

DlProgram::DlProgram() : state_(Waiting) {
		//network_ = make_shared<Network>();
		//addChild(network_->configuration());

	shared_ptr<Configuration> configTrain = 
		make_shared<Configuration>(this, "dl", Configuration::Select);
	configTrain->items().push_back("train");
	configTrain->items().push_back("test");
	configTrain->items().push_back("stop");
	configuration_->addChild(configTrain);
}

void configurationChanged(shared_ptr<Configuration> configuration) {


	if (configuration->name() == "dl") {
		if (configuration->text() == "train") {
			if (trainState_ == TrainStoped) {
				trainState_ = Training;
				DlProgram::asyncTrain(this);
				printf("Train started.\n");
			}
			else {
				printf("Train already started.\n");
			}

		}
	}
	else 	if (configuration->name() == "test") {
		if (configuration->text() == "start" && testState_ == TestStoped) {
			testState_ = Testing;
			DlProgram::asyncTest(this);
		}
	}
	else {
		return false;
	}

}

/*

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

	std::thread* thread = new std::thread(DlProgram::syncTrain, program);
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

*/





};


