#ifndef __ABC_DEEP_LEARNING_PROGRAM_HEADER__
#define __ABC_DEEP_LEARNING_PROGRAM_HEADER__

#include "abc/program/program.h"
#include "deepnetwork.h"
//#include "caffe/net.hpp"


using namespace std;

namespace abc {

typedef float DType;	

class DlProgram : public Program {

public:
	//enum State { Waiting = 0, Training, Testing };

	DlProgram();
	virtual ~DlProgram();


	// inherited from Configurable
	virtual void config(Configuration* configuration, const std::string& param);


protected:

	/** @brief inherit from runner */
	virtual bool beforeRuning();

	/** @brief inherit from runner */
	virtual bool step();

	// train step
	virtual bool train_step() { return true; }

	// test step
	virtual bool test_step() { return true; }

	//inline caffe::Net<DType>*& caffe_net() { return caffe_net_; }

	DeepNetwork* network_;

private:

	bool check();
	int check_gpu_count();

	inline const bool& training() const { return training_; }
	inline void set_training(bool b) {
		if (training_ == b) { return; }
		training_ = b;
		if (training_ && testing_) {
			status_status_->text() = "training and testing";
		}
		else if (training_) {
			status_status_->text() = "training";
		}
		else if (testing_) {
			status_status_->text() = "testing";
		}
		else {
			status_status_->text() = "waiting";
		}
	}

	inline const bool& testing() const { return testing_; }
	inline void set_testing(bool b) {
		if (testing_ == b) { return; }
		testing_ = b;
		if (training_ && testing_) {
			status_status_->text() = "training and testing";
		}
		else if (training_) {
			status_status_->text() = "training";
		}
		else if (testing_) {
			status_status_->text() = "testing";
		}
		else {
			status_status_->text() = "waiting";
		}
	}

	inline const bool& use_gpu() const { return use_gpu_; }
	inline void set_use_gpu(bool b) {
		use_gpu_ = b;
		status_use_gpu_->text() = use_gpu_ ? "true" : "false";
	}

	inline const int& gpu_id(int id) const { return gpu_id_; }
	inline void set_gpu_id(int id) { gpu_id_ = id; }

	inline const int& gpu_count() const { return gpu_count_; }


	
	//caffe::Net<DType>* caffe_net_;
	Configuration* status_status_;
	Configuration* status_use_gpu_;
	bool training_;
	bool testing_;
	bool use_gpu_;
	int gpu_id_;
	int gpu_count_;



};


} // namespace abc
#endif // __ABC_DEEP_LEARNING_PROGRAM_HEADER__

