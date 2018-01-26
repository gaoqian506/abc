//#include "markdetectsrc/markdetectprogram.h"
#include "abc/learning/deep/dlprogram.h"

class MarkDetectionProgram : public abc::DlProgram {

public:

	virtual void getInputAndLabel(
		std::shared_ptr<caffe::Blob<DType>>& input, 
		std::shared_ptr<caffe::Blob<DType>>& label
	) {

	}

};

int main(int argc, char** argv) {

	MarkDetectionProgram program;
	return program.run();

}
