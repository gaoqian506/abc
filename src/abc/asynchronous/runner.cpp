#include "abc/asynchronous/runner.h"
#include "abc/configuration/configuration.h"

#include <iostream>	// std::cout

namespace abc {

Runner::Runner() : thread_(0), running_(false) {
	LOG(INFO) << name() << " (Runner)before constrct.";
	set_name("Runner");
	Configuration* action_run = new Configuration(this, Configuration::Action, "run", 
		"", "Start a working subthread.");
	Configuration* action_stop = new Configuration(this, Configuration::Action, "stop", 
		"", "Stop a working subthread.");
	status_running_ = new Configuration(this, Configuration::Status, "running", 
		"false", "If working on subthread.");

	configuration_->add_child(action_run);
	configuration_->add_child(action_stop);
	configuration_->add_child(status_running_);

	add_configuration_for_auto_release(action_run);
	add_configuration_for_auto_release(action_stop);
	add_configuration_for_auto_release(status_running_);

	//set_running(running_);


	LOG(INFO) << name() << " Constructs with children count:" << configuration_->children_count();
	LOG(INFO) << name() << " (Runner)before constrct.";
}

Runner::~Runner() {

	LOG(INFO) << name() << " (Runner)before destroy, thread:" << thread_;
	release_thread();
	LOG(INFO) << name() << " (Runner)after destroy.";
}


void Runner::run() {


	if (running()) {
		LOG(INFO) << name() << " has already been running.\n";
	}
	else {
		release_thread();

		CHECK(thread_ == 0) << name() <<"'s should be zero.";

		set_running(true);
		LOG(INFO) << name() << "(Runner) before starting running thread.\n";	
		thread_ = new std::thread(Runner::staticRun, this);
		LOG(INFO) << name() << "(Runner) after starting running thread.\n";
		//LOG(INFO) << name() << " joinable:" << thread_->joinable() << std::endl;

	}

	
}

void Runner::join() {

	// has thread && thread is running && not this thread
	if (thread_ && thread_->joinable() && 
		thread_->get_id() != std::this_thread::get_id()) {
		thread_->join(); 
	}
}


void Runner::stop() {
	LOG(INFO) << name() << " before stop running thread.\n";
	set_running(false);
	LOG(INFO) << name() << " after stop running thread.\n";

	// if not this thread wait for complete
	if (thread_ && thread_->get_id() != std::this_thread::get_id()) {
		LOG(INFO) << name() << " wait for finish.\n";
		LOG(INFO) << name() << "[Runner] before stop-join.\n";
		join();
		LOG(INFO) << name() << "[Runner] after stop-join.\n";
	}
	
}


void Runner::config(Configuration* configuration, const std::string& param) {

	assert(configuration);

	LOG(INFO) << name() << " will config:" << configuration->name();
	
	if (configuration->name() == "run") {
		run();
	}
	else if (configuration->name() == "stop") {
		stop();
	}
	else {
		LOG(INFO) << this->name() << " before forward command.";
		Configurable::config(configuration, param); 
		LOG(INFO) << this->name() << " after forward command.";
	}

}


void Runner::runLoop() {
	
	//thread_->join();
	LOG(INFO) << name() << "(Runner) before starting run loop in thread.\n";
	if (beforeRuning()) {
		while(running_ && step());
		afterStoped();
	}
	stop();
	//set_running(false);
	LOG(INFO) << name() << "(Runner) after starting run loop in thread.\n";

}

void Runner::release_thread() {


	if (thread_ && thread_->get_id() == std::this_thread::get_id()) {
		LOG(ERROR) << "Can not release Runner object within thread.";
	}

	if (thread_ && thread_->get_id() == std::thread::id()) {
		LOG(INFO) << "Release a empty thread.";
		delete thread_;
		thread_ = 0;
	}

	if (thread_) {
		LOG(INFO) << "Release a rnning thread need stop and join.";
		stop();
		join();
		delete thread_;
		thread_ = 0;
	}

}


 inline void Runner::set_running(bool running) {
		running_ = running;
		status_running_->text() = running ? "true" : "false";
	}

} // namespace abc
