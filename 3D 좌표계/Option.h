#include "particle.h"
#include <GL/freeglut.h>
#include "particle.h"
#ifndef __OPT_H__
#define __OPT_H__
class Option {
public:

	void reset(float particle[8][3][3]);

	void start(float particle[8][3][3]);
};

#endif // !__OPT_H__
