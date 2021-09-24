#include "Equation.h"

double Equation::Dot(double X[]) {
	int L = sizeof(X);
	double sum;
	for (int i = 0; i < L; i+=1) {
		sum = X[i] * X[i];
	}
	return sum;
}

double Equation::C_Pos(double X[]) {
	int L = sizeof(X);
	double sum;
	for (int i = 0; i < L; i += 1) {
		sum = X[i] * X[i];
	}
	return sum;
}

double Equation::L_Pos(double X[]) {
	int L = sizeof(X);
	double sum;
	for (int i = 0; i < L; i += 1) {
		sum = X[i] * X[i];
	}
	return sum;
}
