#include "GL/freeglut.h"
#include "physics.h"
#include <math.h>

Particle N = Particle();

float Physics::Dot(float V1[3], float V2[3]) { // 벡터 내적
	return V1[0] * V2[0] + V1[1] * V2[1] + V1[2] * V2[2];
}

float Physics::Distance(float V1[3]) { // 두 점 사이의 거리
	return (float)pow((pow(V1[0], 2) + pow(V1[1], 2) + pow(V1[2], 2)), 0.5);
}


void Physics::G_Force(int i, float particle[8][3][3]) { // 중력 계산
	particle[i][2][1] += G * mass;
}

void Physics::D_Force(int i, float particle[8][3][3]) { // 항력 계산
	for (int j = 0; j <= 2; j++) {
		particle[i][2][j] += -Kd * particle[i][1][j];
	}
}

void Physics::S_Force(float particle[8][3][3]) {// 탄성력 계산
	float X_Delta[3];
	float V_Delta[3];
	for (int i = 0; i < N.num - 1; i++) {
		for (int j = i + 1; j < N.num; j++) {
			for (int t = 0; t <= 2; t++) {
				X_Delta[t] = particle[i][0][t] - particle[j][0][t];
				V_Delta[t] = particle[i][1][t] - particle[j][1][t];
			}
			for (int t = 0; t <= 2; t++) {
				particle[i][2][t] += -(Ks * (Distance(X_Delta) - L) + Kd * Dot(V_Delta, X_Delta) / Distance(X_Delta)) * X_Delta[t] / Distance(X_Delta);
				particle[j][2][t] += -particle[i][2][t];
			}
		}
	}
}


void Physics::E_Velocity(int i, float particle[8][3][3]) { // Euler Velocity 속도 계산
	for (int j = 0; j <= 2; j++) {
		particle[i][1][j] += ((float)Time / 1000) * particle[i][2][j] / mass;
	}
}

void Physics::Collision(int i, float particle[8][3][3]) { // 충돌 계산
	if (particle[i][0][1] <= 0) {
		for (int k = 0; k <= 2; k++) {
			V_Delta[k] = particle[i][1][k];
			if (k == 1) {
				X_Delta[k] = particle[i][0][k];
			}
			else {
				X_Delta[k] = 0;
			}
		}
		if (Dot(X_Delta, N_Delta) < e) {
			if (Dot(V_Delta, N_Delta) < 0) {
				for (int j = 0; j <= 2; j++) {
					particle[i][1][j] = -Kr * particle[i][1][j];
				}
			}
		}
	}
}

void Physics::Contact(int i, float particle[8][3][3]) { // 접촉 계산
	float F = sqrt(pow(particle[i][2][0], 2) + pow(particle[i][2][2], 2));
	float angle = atan2(particle[i][2][0], particle[i][2][2]);
	if (particle[i][0][1] <= 0) {
		for (int k = 0; k <= 2; k++) {
			V_Delta[k] = particle[i][1][k];
			if (k == 1) {
				X_Delta[k] = particle[i][0][k];
			}
			else {
				X_Delta[k] = 0;
			}
		}
		if (sqrt(pow(Dot(X_Delta, N_Delta), 2)) < e) {
			if (fabs(Dot(V_Delta, N_Delta)) < e) {
				if (F >= particle[i][2][1] * us) {
					particle[i][2][2] -= uk * particle[i][2][1] * cos(angle);
					particle[i][2][0] -= uk * particle[i][2][1] * sin(angle);
				}
				else {
					for (int j = 0; j <= 2; j++) {
						if (j != 1) {
							particle[i][2][j] = 0;
						}
					}
				}
				particle[i][2][1] = 0;
			}
		}
	}
}