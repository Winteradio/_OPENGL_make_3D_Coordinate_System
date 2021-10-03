#ifndef __PART_H__
#define __PART_H__


class Particle {
public:
	float particle[8][3][3];
	int num = sizeof(particle) / sizeof(particle[0]);
};

#endif
