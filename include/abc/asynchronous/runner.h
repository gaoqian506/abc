#ifndef __ABC_PLAYER_PLAYER_HEADER__
#define __ABC_PLAYER_PLAYER_HEADER__

#include "abc/configuration/configurable.h"

#include <iostream>	// std::cout
#include <thread>	// std::thread



namespace abc {


class Runner : public Configurable{


public:

	Runner();
	virtual ~Runner();
	void run();
	void stop();
	void join();
	inline const bool& running() { return running_; }

	/** @brief inherit from Configuable for some interact. */
	virtual void config(Configuration* configuration, const std::string& param);


protected:
	virtual bool beforeRuning() { return true; }
	virtual void afterStoped() {}

	/** @brief return false if no need more steps. */
	virtual bool step() {return true; }



private:
	static void staticRun(Runner* owner) { owner->runLoop(); }
	void runLoop();
	void release_thread();
	inline void set_running(bool running);

	std::thread* thread_;
	bool running_;
	Configuration* status_running_;



};



} // namespace abc
#endif // __ABC_PLAYER_PLAYER_HEADER__

