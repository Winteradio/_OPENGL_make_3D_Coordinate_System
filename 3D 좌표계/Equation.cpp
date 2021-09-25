#include "Equation.h"
#include <iostream>
#include <vector>

using namespace std;

double Equation::Dot(double X[]) {
	int L = sizeof(X);
	double sum;
	for (int i = 0; i < L; i+=1) {
		sum = X[i] * X[i];
	}
	return sum;
}

void Equation::degree(double X[]) {
	for (int i = 1; i <= sizeof(X); i++) {
		if (X[i] >= 360) {
			X[i] -= 360;
		}
	}
}

void Equation::calculate(double X1[],double X2[]) {
	X2[0] = X1[0] * cos(X1[1]) * cos(X1[2]);
	X2[1] = X1[0] * cos(X1[1]) * sin(X1[2]);
	X2[2] = X1[0] * sin(X1[1]);
}

void Equation::bright_X(double cx[], float Y) {

}

void Equation::bright_Y(double cx[], float X) {

}
