#ifndef __ABC_ASYNCHRONOUS_ASYNCHRONOUS_HEADER__
#define __ABC_ASYNCHRONOUS_ASYNCHRONOUS_HEADER__


#include <memory>	// shared_ptr
#include <thread>	// thread
#include <glog/logging.h>


using namespace std;

namespace abc {

class Asynchronous {

public:

	Asynchronous() : exit_(false) {}

	void asyncBegin(void* param = 0) {
		thread_ = make_shared<thread>(syncBegin, this, param);
		LOG(INFO) << "A thread stated.";
	}

	void join() {
		thread_->join();
	}
	
	virtual void end() {}
	

protected:

	static void syncBegin(Asynchronous* target, void* param) {
		target->begin(param);
	}
	virtual void begin(void* param) {}

	shared_ptr<thread> thread_;
	bool exit_;

};



} // namespace abc
#endif // __ABC_ASYNCHRONOUS_ASYNCHRONOUS_HEADER__

