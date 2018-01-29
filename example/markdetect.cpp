#include "abc/learning/deep/dlprogram.h"

class MarkDetectionProgram : public abc::DlProgram {

public:

	MarkDetectionProgram() {

		Configuration config_background_dir("background_dir", Configuration::Text);
		Configuration config_mark_dir("mark_dir", Configuration::Text);
		Configuration config_test_dir("test_dir", Configuration::Text);
		Configuration config_output_dir("output_dir", Configuration::Text);

		configuration()->addChild(config_background_dir);
		configuration()->addChild(config_mark_dir);
		configuration()->addChild(config_test_dir);
		configuration()->addChild(config_output_dir);

	}




	virtual void trainStep() {


		int count = getRandom();
		cv::Mat data = Image::read(train_backgrounds, random = true);
		cv::Mat label = cv::Mat(back.size. 0);
		for (int i = 0; i < count; i++) {
			cv::Mat mark = Image::read(train_marks, random = true, &index);
			int class = parseClass(train_marks[index]);
			cv::Mat mask = Image::overlap(data, mark);
			label.set(mask, index);
		}

		network_->setBlob(Converter::convert(data), "data");
		network_->setBlob(Converter::convert(label), "label");

		network->learn();


	}

	virtual void testStep() {

		static int index = 0;
		if (index >= test_images.size()) {
			testState_ = TestStoped; 
		}
		else {
			cv::Mat test = Image::read(test_images[index]);
			network_->setBlob(Converter::convert(data), "data");
			network_->forward();
			Image::save(output_dir+test_images[index], convert(network->getBlob("output"));
			index++;
		}

	}

};

int main(int argc, char** argv) {

	MarkDetectionProgram program;
	return program.run();

}
