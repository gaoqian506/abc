#include "abc/deeplearning/dlprogram.h"


namespace abc {

DlProgram::DlProgram() {

	set_name("dlprogram");
	configuration_->name() = "dlprogram";
	network_ = new DeepNetwork();
	training_ = false;
	testing_ = false;
	use_gpu_ = true;
	gpu_id_ = 0;
	gpu_count_ = check_gpu_count();


	Configuration* action_train = new Configuration(this, Configuration::Action, 
		"train", "", "Start training.");
	Configuration* action_test = new Configuration(this, Configuration::Action, 
		"test", "", "Start testing.");	
	Configuration* text_stop = new Configuration(this, Configuration::Text, 
		"stop", "", "Stop train or test.");
	Configuration* text_swith = new Configuration(this, Configuration::Action, 
		"switch", "", "Switch mode between gpu and cpu.");	
	Configuration* text_gpu_id = new Configuration(this, Configuration::Text,
		"gpu_id", "0", "Specify which gpu will be used.");
	status_status_ = new Configuration(this, Configuration::Status, 
		"status", "waiting", "Training, testing or waiting.");
	status_use_gpu_ = new Configuration(this, Configuration::Status, 
		"use_gpu", "true", "Using GPU when train or test.");	
	Configuration* status_gpu_count = new Configuration(this, Configuration::Status, 
		"gpu_count", std::to_string(gpu_count_), "GPU count in this machine.");

	configuration_->add_child(action_train);
	configuration_->add_child(action_test);
	configuration_->add_child(text_stop);
	configuration_->add_child(text_swith);
	configuration_->add_child(text_gpu_id);
	configuration_->add_child(status_status_);
	configuration_->add_child(status_use_gpu_);
	configuration_->add_child(status_gpu_count);

	add_configuration_for_auto_release(action_train);
	add_configuration_for_auto_release(action_test);
	add_configuration_for_auto_release(text_stop);
	add_configuration_for_auto_release(text_swith);
	add_configuration_for_auto_release(text_gpu_id);
	add_configuration_for_auto_release(status_status_);
	add_configuration_for_auto_release(status_use_gpu_);
	add_configuration_for_auto_release(status_gpu_count);

	configuration_->child("run")->mute() = true;
	configuration_->child("stop")->mute() = true;
	//configuration_->child("running")->mute() = true;

}

DlProgram::~DlProgram() {
	LOG(INFO) << name() << "[DlProgram]: before destroy.";
	stop();
	if (network_) { 
		delete network_;
	}
	LOG(INFO) << name() << "[DlProgram]: after destroy.";
}

void DlProgram::config(Configuration* configuration, const std::string& param) {

	assert(configuration);

	LOG(INFO) << name() << " will config:" << configuration->name();
	
	if (configuration->name() == "train") {
		LOG(INFO) << name() << " before start training.";
		set_training(true);
		if (!running()) { run(); }
		LOG(INFO) << name() << " after start training.";

	}
	else if (configuration->name() == "test") {
		set_testing(true);
		if (!running()) { run(); }
	}
	else if (configuration->name() == "stop") {
		if (param == "train") {
			LOG(INFO) << this->name() << ": before stop train.";
			set_training(false); 
			LOG(INFO) << this->name() << ": after stop train:" << training() <<".";
		}
		else if (param == "test") {
			LOG(INFO) << this->name() << ": before stop test.";
			set_testing(false);
			LOG(INFO) << this->name() << ": after stop test:" << testing() <<".";
		}
		else {
			LOG(INFO) << name() << " only train or test is acceptable to stop.";
		}
	}
	else if (configuration->name() == "switch") {
		set_use_gpu(!use_gpu());
	}
	else if (configuration->name() == "gpu_id") {
		try {
			int id = std::stoi(param);	
			if (id >= gpu_count()) {
				LOG(INFO) << name() << ": gpu id " << param << 
					" is too large than gpu count[" << gpu_count()
					<< "] or there is no gpu on this machine.";
			}
			else { 
				set_gpu_id(id); 
				configuration->text() = param;
			}
		}
		catch (std::invalid_argument) {
			LOG(INFO) << name() << ": please specify a valid number.";
		}
		catch (std::out_of_range) {
			LOG(INFO) << name() << ": the specified number(" << param
				<< ") is out of range.";
		}

	}	
	else {
		LOG(INFO) << this->name() << " before forward command.";
		Program::config(configuration, param); 
		LOG(INFO) << this->name() << " after forward command.";
	}


}

bool DlProgram::beforeRuning() {
	bool ok = check();
	if (!ok) {
		set_training(false);
		set_testing(false);
	}
//LOG(INFO) << "-----------------------------------"<<use_gpu();
	caffe::Caffe::set_mode(use_gpu() ? caffe::Caffe::GPU : caffe::Caffe::CPU);
	caffe::Caffe::SetDevice(gpu_id());


	return ok;
}

bool DlProgram::check() {

#ifdef CPU_ONLY
	if (use_gpu()) {
		LOG(INFO) << name() << " chouldn't use gpu when compiled with CPU_ONLY.";
		return false;
	}
	LOG(WARNING) << name() << " will run in CPU mode.";

#else
	if (use_gpu() && gpu_count() == 0) {
		LOG(INFO) << name() << ": therer is no gpu in this machine.";
		return false;
	}
	else if (use_gpu() && gpu_id() >= gpu_count()) {
		LOG(INFO) << name() << ": gpu_id(" << gpu_id() <<
			") is too large than " << gpu_count();
		return false;
	}
	else if (use_gpu()) {
		LOG(INFO) << name() << " will run in GPU mode.";
	}
	else if (!use_gpu()) {
		LOG(WARNING) << name() << " will run in CPU mode.";	
	}
	else {
		LOG(WARNING) << name() << ": should no other else.";
		return false;	
	}


#endif

	return true;

}

int DlProgram::check_gpu_count() {

	LOG(INFO) << name() << ": before check gpu count.";
    int count = 0;
#ifndef CPU_ONLY
    CUDA_CHECK(cudaGetDeviceCount(&count));
#else
    count = 0;
#endif
	LOG(INFO) << name() << ": after check gpu count: " << count << ".";    
	return count;	
}


bool DlProgram::step() {

	bool goon = training() && train_step() || testing() && test_step();

	if (!goon) {
		set_training(false);
		set_testing(false);
	}
	return goon;

}



} // namespace abc


