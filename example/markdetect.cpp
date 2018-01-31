#include "abc/learning/deep/dlprogram.h"
#include "abc/image/image.h"
#include "abc/configuration/consoleconfigurator.h"

#include <opencv2/highgui/highgui.hpp>

using namespace abc;
using namespace std;

class MarkDetectionProgram : public DlProgram {

public:

	MarkDetectionProgram(int argc, char** argv) : 
		DlProgram("example/data/markdetect/fcn-16s.pt") {

		int id = static_cast<int>(2.5);
		cout << id << " id.\n";

		shared_ptr<Configuration> config_background_dir = 
			make_shared<Configuration>(this, "background_dir", Configuration::Text);
		shared_ptr<Configuration> config_mark_dir = 
			make_shared<Configuration>(this, "mark_dir", Configuration::Text);
		shared_ptr<Configuration> config_test_dir = 
			make_shared<Configuration>(this, "test_dir", Configuration::Text);
		shared_ptr<Configuration> config_output_dir = 
			make_shared<Configuration>(this, "output_dir", Configuration::Text);

		configuration_->addChild(config_background_dir);
		configuration_->addChild(config_mark_dir);
		configuration_->addChild(config_test_dir);
		configuration_->addChild(config_output_dir);

		if (argc > 1) {

			ConsoleConfigurator cc(configuration_);
			cc.parseFile(argv[1]);
		}
	}

	virtual void configurationChanged(shared_ptr<Configuration> configuration) {


			if (configuration->name() == "background_dir") {
				backgroundNames_ = Image::find(configuration->text());
			}
			else if (configuration->name() == "mark_dir") {
				markNames_ = Image::find(configuration->text());
			}
			else if (configuration->name() == "test_dir") {
				testNames_ = Image::find(configuration->text());
			}
			else if (configuration->name() == "output_dir") {
				output_dir_ = configuration->text();
			}
			else {
				DlProgram::configurationChanged(configuration);
			}

	}

	// train step
	virtual void trainStep() {

		if (backgroundNames_.size() == 0 || markNames_.size() == 0) {
			cout << "Please specify the backgournd and mark directory." << endl;
		}

		int count = rand() % 10;
		const std::string& backName = random(backgroundNames_);
		cv::Mat data = cv::imread(backName);
		cv::Mat label = cv::Mat(data.size(), CV_32F, cv::Scalar(0));
		for (int i = 0; i < count; i++) {
			const std::string& markName = random(markNames_);
			cv::Mat mark = cv::imread(markName);
			int classId = parseClass(markName);
			cv::Mat mask = abc::Image::overlap(data, mark);
			label.setTo(classId, mask);
		}

		cout << "train step.\n";

		data.convertTo(data, CV_32F, 1.0/255.0);
		//label.convertTo(label, CV_32F, 1.0/255.0);

		cout << "data type:" << data.type() << endl;
		//cout << "label type:" << label.type() << endl;

		network_->setBlob(data, "data");
		network_->setBlob(label, "label");
		//network_->setBlob(abc::Converter::convert(data), "data");
		//network_->setBlob(abc::Converter::convert(label), "label");

		network_->forward();
		network_->backward();
		//network->learn();
	}

	// test step
	virtual void testStep() {

	}

private:

	inline string& random(vector<string>& names) {
		return names[rand() % names.size()];
	}

	int parseClass(const std::string& name) {
		return 0;
	}


	vector<string> backgroundNames_;
	vector<string> markNames_;
	vector<string> testNames_;
	string output_dir_;


};

int main(int argc, char** argv) {

	MarkDetectionProgram program(argc, argv);
	return program.run();

}
