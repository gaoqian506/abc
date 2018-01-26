#include "abc/learning/deep/dlprogram.h"


namespace abc {


DlProgram::DlProgram() {

	Configuration configTrain("train", Configuration::Select);
	configTrain.items().push_back("start");
	configTrain.items().push_back("pause");
	configTrain.items().push_back("resume");
	configTrain.items().push_back("stop");

	configuration()->addChild(configTrain);

}

bool DlProgram::configurationChanged(Configuration* configuration) {
	if (configuration->name() == "train") {
		if (configuration->text() == "start") {
			train(Start);
		}
	}
	else {
		return false;
	}
}

void DlProgram::train(TrainFlag flag/* = Start*/) {

		std::shared_ptr<caffe::Blob<DType>> input;
		std::shared_ptr<caffe::Blob<DType>> label;
	while(true) {

		getInputAndLabel(input, label);
		network->learn(input, label);
	}

}





};


