#include "option.h"
#include <random>
#include <iostream>

using namespace std;
Particle n = Particle();

void Option::reset(float particle[8][3][3]) {
	for (int i = 0; i < n.num; i++) {
		for (int j = 0; j <= 2; j++) {
			particle[i][2][j] = 0;
		}

	}
}

void Option::start(float particle[8][3][3]) {
	for (int i = 0; i < n.num; i++) {
		for (int j = 0; j <= 1; j++) {
			for (int k = 0; k <= 2; k++) {
				particle[i][j][k] = (float)(rand() % 4);
			}
		}
	}
}