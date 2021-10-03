#include <vector>
#ifndef __EQU_H__
#define __EQU_H__

class Equation {
public:

	double Dotproduct(double X1[3],double X2[3]);

	void externalproudct(double X1[3], double X2[3], double X3[3]);

	void Cubetoplane_1(double CX[3], double CY[3], double POS[3],double ratio[2]);
	
	void Cubetoplane_2(double ratio[2], int P_WIDTH, int WIDTH, int P_HEIGHT, int HEIGHT, double WIN[2]);

	void Planetovector(double CX[3], double CY[3], int WIN[2],double POS[3], int P_WIDTH, int P_HEIGHT);

	void Rotate(double camera[3], double PV[3]);

	void Upvector(double CX[3], double Up[3]);

	void calculate(double X1[],double X2[]);
};
#endif // !__EQU_H__
