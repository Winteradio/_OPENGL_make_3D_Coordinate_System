#include "Equation.h"
#include <iostream>
#include <vector>

using namespace std;

double Equation::Dotproduct(double X1[3],double X2[3]) {
	double sum=0;
	for (int i = 0; i < 3; i+=1) {
		sum += X1[i] * X2[i];
	}
	return sum;
}

void Equation::externalproudct(double X1[3], double X2[3],double X3[3]) {
	X3[0] = X1[1] * X2[2] - X1[2] * X2[1];
	X3[1] = X1[2] * X2[0] - X1[0] * X2[2];
	X3[2] = X1[0] * X2[1] - X1[1] * X2[0];
}

void Equation::Cubetoplane_1(double CX[3], double CY[3], double POS[3], double ratio[2]) {
	double Up[3], NU[3];
	NU[0] = CX[2];
	NU[1] = 0;
	NU[2] = -CX[0];
	externalproudct(CX, NU, Up);
	for (int i = 0; i <= 2; i++) {
		POS[i] = POS[i] - CY[i];
	}

	double X, Y, Z;
	X = Dotproduct(POS, NU)/sqrt(Dotproduct(NU,NU));
	Y = Dotproduct(POS, Up)/ sqrt(Dotproduct(Up, Up));
	Z = sqrt(Dotproduct(CX, CX)) - Dotproduct(POS, CX) / sqrt(Dotproduct(CX, CX));
	ratio[0] = X / Z;
	ratio[1] = Y / Z;
}

void Equation::Cubetoplane_2(double ratio[2],int P_WIDTH,int WIDTH,int P_HEIGHT, int HEIGHT,double WIN[2]) {
	WIN[0] = (double)P_WIDTH / 2 + (double)WIDTH * ratio[0]/2;
	WIN[1] = (double)P_HEIGHT / 2 - (double)HEIGHT * ratio[1]/2;
}

void Equation::Planetovector(double CX[3], double CY[3], int WIN[2],double POS[3], int P_WIDTH, int P_HEIGHT) {
	double Up[3], NU[3];
	NU[0] = CX[2];
	NU[1] = 0;
	NU[2] = -CX[0];
	externalproudct(CX, NU, Up);
	for (int i = 0; i <= 2; i++) {
		NU[i] = NU[i] / sqrt(Dotproduct(NU, NU));
		Up[i] = Up[i] / sqrt(Dotproduct(Up, Up));
	}
	double win[2];
	win[0] = (double)(WIN[0] - (double)P_WIDTH / 2)/((double)P_WIDTH / 2);
	win[1] = (double)(-WIN[1] + (double)P_HEIGHT / 2)/ ((double)P_HEIGHT / 2);
	for (int i = 0; i <= 2; i++) {
		NU[i] *= win[0];
		Up[i] *= win[1];
	}
	for (int i = 0; i <= 2; i++) {
		POS[i] = Up[i]+NU[i];
	}
}

void Equation::Upvector(double CX[3], double Up[3]) {
	double U[3], NU[3];
	for (int i = 0; i <= 2; i++) {
		U[i] = CX[i];
	}
	NU[0] = U[2];
	NU[1] = 0;
	NU[2] = -U[0];
	externalproudct(U, NU, Up);
}

void Equation::calculate(double X1[],double X2[]) {
	X2[0] = X1[0] * cos(X1[2]) * sin(X1[1]);
	X2[1] = X1[0] * sin(X1[2]);
	X2[2] = X1[0] * cos(X1[2]) * cos(X1[1]);
}

void Equation::Rotate(double camera[3], double PV[3]) {
	double CX[3],Up[3], NU[3];
	calculate(camera, CX);
	NU[0] = CX[2];
	NU[1] = 0;
	NU[2] = -CX[0];
	externalproudct(CX, NU, Up);

	double X, Y;
	double A_angle, B_angle;

	X = Dotproduct(NU, PV) / sqrt(Dotproduct(NU, NU));
	Y = Dotproduct(Up, PV) / sqrt(Dotproduct(Up, Up));
	camera[1] -= 0.15 * (atan(X / camera[0]));
	if (camera[1] >= 3.141*2) {
		camera[1] -= 3.141 * 2;
	}
	else if (camera[1] <= 0) {
		camera[1] += 3.141 * 2;
	}
	camera[2] -= 0.15 * (atan(Y / camera[0]));
	if (camera[2] >= 3.141*89/180) {
		camera[2] = 3.141 * 89 / 180;
	}
	else if (camera[2] <= -3.141 * 89 / 180)
	{
		camera[2] = -3.141 * 89 / 180;
	}

}

