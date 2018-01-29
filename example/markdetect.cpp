#include "abc/learning/deep/dlprogram.h"
#include "abc/image/image.h"
#include "abc/learning/deep/converter.h"
#include "abc/configuration/consoleconfigurator.h"

#include <opencv2/highgui/highgui.hpp>

class MarkDetectionProgram : public abc::DlProgram {

public:

	MarkDetectionProgram(int argc, char** argv) {

		network_ = new abc::Network("example/data/markdetect/net.pt");

		abc::Configuration config_background_dir("background_dir", abc::Configuration::Text);
		abc::Configuration config_mark_dir("mark_dir", abc::Configuration::Text);
		abc::Configuration config_test_dir("test_dir", abc::Configuration::Text);
		abc::Configuration config_output_dir("output_dir", abc::Configuration::Text);

		configuration()->addChild(config_background_dir);
		configuration()->addChild(config_mark_dir);
		configuration()->addChild(config_test_dir);
		configuration()->addChild(config_output_dir);

		if (argc > 1) {
			abc::ConsoleConfigurator cc;
			cc.begin(this, argv[1]);
		}

	}

	virtual bool configurationChanged(abc::Configuration* configuration) {
		if (abc::DlProgram::configurationChanged(configuration)) {
			return true;
		}

		if (configuration->name() == "background_dir") {
			backgroundNames_ = abc::Image::find(configuration->text());
		}
		else if (configuration->name() == "mark_dir") {
			markNames_ = abc::Image::find(configuration->text());
		}
		else if (configuration->name() == "test_dir") {
			testNames_ = abc::Image::find(configuration->text());
		}
		else if (configuration->name() == "output_dir") {
			output_dir_ = configuration->text();
		}
		else {
			return false;
		}
	}




	virtual void trainStep() {

		//assert(backgroundNames_.size() > 0 && markNames_.size() > 0);

		int count = rand() % 10;
		const std::string& backName = random(backgroundNames_);
		cv::Mat data = cv::imread(backName);
		cv::Mat label = cv::Mat(data.size(), CV_8U, 0);
		for (int i = 0; i < count; i++) {
			const std::string& markName = random(markNames_);
			cv::Mat mark = cv::imread(markName);
			int classId = parseClass(markName);
			cv::Mat mask = abc::Image::overlap(data, mark);
			label.setTo(classId, mask);
		}

		network_->setBlob(data, "data");
		//network_->setBlob(abc::Converter::convert(data), "data");
		//network_->setBlob(abc::Converter::convert(label), "label");

		//network->learn();


	}

	virtual void testStep() {


		static int index = 0;
		if (index >= testNames_.size()) {
			testState_ = TestStoped; 
		}
		else {
			cv::Mat test = cv::imread(testNames_[index]);
			//network_->setBlob(Converter::convert(data), "data");
			//network_->forward();
			//Image::save(output_dir+test_images[index], convert(network->getBlob("output"));
			index++;
		}


	}

protected:

	int parseClass(const std::string& name) {
		return 0;
	}
	std::string& random(std::vector<std::string>& names) {
		assert(names.size() > 0);
		return names[rand() % names.size()];
	}

	std::vector<std::string> backgroundNames_;
	std::vector<std::string> markNames_;
	std::vector<std::string> testNames_;
	std::string output_dir_;

};

int main(int argc, char** argv) {

	MarkDetectionProgram program(argc, argv);
	return program.run();

}
