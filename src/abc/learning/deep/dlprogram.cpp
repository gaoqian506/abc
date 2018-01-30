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

void DlProgram::configurationChanged(shared_ptr<Configuration> configuration) {


	if (configuration->name() == "dl") {
		if (configuration->text() == "train") {
			state_ = Training;
			asyncBegin();
		}
		else if (configuration->text() == "test") {
			state_ = Testing;
			asyncBegin();
		}
		else if (configuration->text() == "stop") {
			state_ = Waiting;
		}
	}
}

void DlProgram::begin(void* param) {
	while(state_ != Waiting) {
		switch (state_) {
		case Training:
			trainStep();
			break;
		case Testing:
			testStep();
			break;
		}
	}
}





} // namespace abc


