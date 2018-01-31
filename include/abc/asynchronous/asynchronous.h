#ifndef __ABC_ASYNCHRONOUS_ASYNCHRONOUS_HEADER__
#define __ABC_ASYNCHRONOUS_ASYNCHRONOUS_HEADER__


#include <memory>	// shared_ptr
#include <thread>	// thread

using namespace std;

namespace abc {

class Asynchronous {

public:

	void asyncBegin(void* param = 0) {
		thread_ = make_shared<thread>(syncBegin, this, param);
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

