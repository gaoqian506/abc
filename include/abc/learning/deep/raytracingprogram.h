#ifndef __ABC_LEARNING_DEEP_RAYTRACING_PROGRAM_HEADER__
#define __ABC_LEARNING_DEEP_RAYTRACING_PROGRAM_HEADER__

#include "abc/learning/deep/deeplearningprogram.h"
#include "abc/graphics/raytracerenderer.h"


namespace abc {

class RaytracingProgram : public DeepLearningProgram {

public:

	RaytracingProgram(int& argc, char**& argv);

	virtual void getInput();
	virtual void getLabel();



protected:
	RaytraceRenderer* renderer;

};


} // namespace abc
#endif // __ABC_LEARNING_DEEP_RAYTRACING_PROGRAM_HEADER__

