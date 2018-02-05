#include "abc/example/mark.h"
#include "abc/configuration/consoleconfigurator.h"
#include "abc/imageprocessing/imageprocessing.h"


namespace example {


Mark::Mark(const int& argc, const char** argv) {

	set_name("mark");
	configuration_->name() = "mark";
	max_size_ = 640;

	//google::InitGoogleLogging(argv[0]);
	//FLAGS_alsologtostderr = 1;

	LOG(INFO) << "[Mark] Before loading network from file.";
	network_->load("example/data/mark/fcn-16s.pt");
	LOG(INFO) << "[Mark] After loading network from file.";

	abc::Configuration* text_back = new abc::Configuration(this, abc::Configuration::Text, 
		"back_dir", "", "Directory stored backgournd images.");
	abc::Configuration* text_mark = new abc::Configuration(this, abc::Configuration::Text, 
		"mark_dir", "", "Directory stored template images.");
	abc::Configuration* text_test = new abc::Configuration(this, abc::Configuration::Text, 
		"test_dir", "", "Directory stored test images.");
	abc::Configuration* text_out = new abc::Configuration(this, abc::Configuration::Text, 
		"out_dir", "", "Directory to which images will wirte.");
	abc::Configuration* text_max = new abc::Configuration(this, abc::Configuration::Text, 
		"max_size", "640", "Max size the image will resize to.");

	configuration_->add_child(text_back);
	configuration_->add_child(text_mark);
	configuration_->add_child(text_test);
	configuration_->add_child(text_out);
	configuration_->add_child(text_max);

	add_configuration_for_auto_release(text_back);
	add_configuration_for_auto_release(text_mark);
	add_configuration_for_auto_release(text_test);
	add_configuration_for_auto_release(text_out);
	add_configuration_for_auto_release(text_max);

	if (argc > 1) {
		abc::ConsoleConfigurator cc;
		cc.add_configuration(configuration_);
		cc.parse_file(argv[1]);
	}

}

Mark::~Mark() {
	LOG(INFO) << name() << "[Mark]: before destroy.";
	stop();
	LOG(INFO) << name() << "[Mark]: after destroy.";
}


void Mark::config(abc::Configuration* configuration, const std::string& param) {

	LOG(INFO) << "[Mark] before config " << configuration->name();
	if (configuration->name() == "back_dir") {
		configuration->text() = param;
		back_names_ = abc::ImageProcessing::find(param);
	}
	else if (configuration->name() == "mark_dir") {
		configuration->text() = param;
		mark_names_ = abc::ImageProcessing::find(param);
	}
	else if (configuration->name() == "test_dir") {
		configuration->text() = param;
		test_names_ = abc::ImageProcessing::find(param);
	}
	else if (configuration->name() == "out_dir") {
		configuration->text() = param;
		out_dir_ = param;
	}
	else if (configuration->name() == "max_size") {
		try {
			int ms = std::stoi(param);
			if (ms <= 0) {
				LOG(INFO) << "Max size \"" << param << "\" must larger than zero.";
			}
			else { 
				configuration->text() = param;
				max_size_ = ms;
			}
		}
		catch (std::invalid_argument) {
			LOG(INFO) << "Cann't convert \"" << param << "\" to a integer.";
		}
		catch (std::out_of_range) {
			LOG(INFO) << "Max size of \"" << param << "\" is out of range.";
		}		
	}
	
	else {
		DlProgram::config(configuration, param);
	}

	LOG(INFO) << "[Mark] after config " << configuration->name();
}

bool Mark::train_step() {

	LOG(INFO) << "[Mark] before train step.";

	static int times = 0;

	if (back_names_.size() == 0 || mark_names_.size() == 0) {
		cout << "Please specify the backgournd and mark directory." << endl;
	}

	int count = rand() % 10;
	cv::Mat data = abc::ImageProcessing::random_read(back_names_);
	data = abc::ImageProcessing::resize(data, max_size_);
	cv::Mat label = cv::Mat(data.size(), CV_32F, cv::Scalar(0));
	int name_id;
	for (int i = 0; i < count; i++) {
		cv::Mat mark = abc::ImageProcessing::random_read(mark_names_, &name_id);
		int classId = 1;//abc::ImageProcessing::parse_first_num(mark_names_[name_id]);
		cv::Mat mask = abc::ImageProcessing::overlap(data, mark, 0.3, 0.5);
		label.setTo(classId, mask);
	}

	cv::Mat data_32f = abc::ImageProcessing::convert(data, CV_32F, 1.0/255.0);

	if(caffe::Caffe::mode()== caffe::Caffe::GPU){
		LOG(INFO) << "~~~~~~~~~~~~~[Mark] will train with GPU.";
	}
	else {
		LOG(INFO) << "~~~~~~~~~~~~~~~~~[Mark] will train with CPU.";
	}
	network_->setBlob(data_32f, "data");
	network_->setBlob(label, "label");


	network_->forward();
	network_->backward();
	//network->learn();



	LOG(INFO) << "[Mark] after train step.";

	return true;
}

bool Mark::test_step() {

	LOG(INFO) << "[Mark] before test step.";
	return true;
	LOG(INFO) << "[Mark] before test step.";
}

} //namespace abc::example
