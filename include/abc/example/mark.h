#ifndef __ABC_EXAMPLE_MARK_HEADER__
#define __ABC_EXAMPLE_MARK_HEADER__


#include "abc/deeplearning/dlprogram.h"


namespace example {


class Mark : public abc::DlProgram {

public:

	Mark(const int& argc, const char** argv);
	~Mark();

	// inherited from DlProgram
	virtual void config(abc::Configuration* configuration, const std::string& param);

	// inherit from dlprogram
	virtual bool train_step();

	// inherit from dlprogram
	virtual bool test_step();

protected:

	std::vector<string> back_names_;
	std::vector<string> mark_names_;
	std::vector<string> test_names_;
	std::string out_dir_;
	int max_size_;

};


} // namespace example

#endif // __ABC_EXAMPLE_MARK_HEADER__

