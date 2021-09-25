#include <gl/freeglut.h>
#include <math.h>
#include <gl\glut.h>
#include <gl\gl.h>
#include <gl\glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "Equation.h"

using std::cout; 
using std::endl; 


Equation E = Equation();

// 극좌표계
double camera[3] = { 5.0f,45.0f,45.0f }; // 카메라의 극 좌표계 { 반지름 , XY 평면 각도, Z 축 각도}

// 직교 좌표계
double CX[3];                           // CX : 카메라 위치의 직교 좌표계
double up[3] = { 0.0f,0.0f,1.0f };      // 카메라 상단의 직교 좌표계
double CY[3] = { 0,0,0 };               // 카메라 초점의 직교 좌표계

// 마우스의 상태 표현
int drag;   // drag 0 : 아무것도 누르지 않은 상태
            // drag 1 : 마우스 왼쪽 키를 누른 상태
            // drag 2 : 마우스 오른쪽 키를 누른 상태

// 윈도우 내에서의 마우스 위치 및 이동 반경 변수
double mousePos[2];
double mouseMove[2];

// 윈도우 창의 크기
int WIDTH = 400, HEIGHT = 400;

// OpenGL Timer 함수 간격
int Time = 10;


void P_Timer(int value) {
    glutTimerFunc(Time, P_Timer, 0);
}

void C_Timer(int value) {
    E.degree(camera);
    if (drag == 1 || drag ==0) {
        E.calculate(camera, CX);
    }
    else if (drag == 2) {
        double CX1[3];
        E.calculate(camera, CX);
        camera[0] = sqrt(pow(camera[0], 2) + E.Dot(mouseMove));
        camera[1] -= atan2(mouseMove[1], camera[0]) / (3.14);
        camera[2] += atan2(mouseMove[0], camera[0]) / (3.14);
        E.calculate(camera, CX1);
        for (int i = 0; i <= 2; i++) {
            CY[i] += CX1[i]-CX[i];
            CX[i] = CX1[i];
        }
        
    }
    glLoadIdentity();
    gluLookAt(CX[0],CX[1],CX[2],-CX[0]+CY[0] , -CX[1] + CY[1] , -CX[2] + CY[2], up[0], up[1], up[2]);
    glutPostRedisplay();
    glutTimerFunc(Time, C_Timer, 0);
}

void changesize(int w, int h)
{
    // 창이 너무 작아졌을때 0 으로 나뉘는 것을 방지합니다.
    if (h == 0)
        h = 1;

    double ratio = 1.0f * w / h;
    // 좌표계를 수정하기 전에 초기화합니다.
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // 뷰포트를 창 전체크기로 설정합니다. 
    glViewport(0, 0, w, h);

    // 절단 공간을 설정합니다.
    gluPerspective(60, ratio, 1, 1000);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(CX[0], CX[1], CX[2], -CX[0] + CY[0], -CX[1] + CY[1], -CX[2] + CY[2], up[0], up[1], up[2]);
}

void mouse_click(int button, int state, int x, int y) {
    switch (button) {
    case GLUT_LEFT_BUTTON:
        if (state == GLUT_DOWN) {
            drag = 1;
            mousePos[0] = (double)(x-WIDTH/2)*2/WIDTH;
            mousePos[1] = (double)(y-HEIGHT/2)*2/HEIGHT;

        }
        else {
            drag = 0;
        }
        break;
    case GLUT_RIGHT_BUTTON:
        if (state == GLUT_DOWN) {
            drag = 2;
            mousePos[0] = (double)(x - WIDTH / 2) * 2 / WIDTH;
            mousePos[1] = (double)(y - HEIGHT / 2) * 2 / HEIGHT;
        }
        else {
            drag = 0;
        }
        break;
    }
}
void mouse_move(int x, int y) {
    if (drag != NULL) {
        mouseMove[0] = (double)(x-WIDTH/2)*2/WIDTH - mousePos[0];
        mouseMove[1] = (double)(y-HEIGHT/2)*2/HEIGHT - mousePos[1];

        if (drag == 1) {
            camera[2] += atan2(mouseMove[0], camera[0]) / (3.14);
            camera[1] -= atan2(mouseMove[1], camera[0]) / (3.14);
        }
    }
}

void mouse_wheel(int button, int dir, int x, int y) {
    if (dir > 0) {
        camera[0] = camera[0] / 2;
    }
    else {
        camera[0] = camera[0] * 2;
    }
    return;
}

void coordinatesystem(void) // 
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // 지형을 그립니다.
    glColor3f(0.5f, 0.5f, 0.5f);
    glBegin(GL_QUADS);
    glVertex3f(-100.0f, -100.0f, 0.0f);
    glVertex3f(-100.0f, 100.0f, 0.0f);
    glVertex3f(100.0f, 100.0f, 0.0f);
    glVertex3f(100.0f, -100.0f, 0.0f);
    glEnd();

    float num = 0;
    while (num <= 200) {
        glColor3f(1.0f, 1.0f, 1.0f);
        glBegin(GL_POINTS);
        glVertex3f(-100, -100 + num, 0);
        glVertex3f(100, -100 + num, 0);
        glVertex3f(-100 + num, -100, 0);
        glVertex3f(-100 + num, 100, 0);
        glEnd();
        num += 1;
    }
    float matrix[3][3] = { {1,0,0},{0,1,0},{0,0,1} };
    for (int i = 0; i <= 2; i++) {
        glColor3f(1.0f, 0.0f, 0.0f);
        glBegin(GL_LINES);
        glVertex3f(5.0 * matrix[i][0], 5.0 * matrix[i][1], 5.0 * matrix[i][2]);
        glVertex3f(-5.0 * matrix[i][0], -5.0 * matrix[i][1], -5.0 * matrix[i][2]);
        glEnd();
    }


    glutSwapBuffers();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow("3D Coordinate System");
    glClearColor(0.0, 0.0, 0.0, 0.0);
    
    // 시간에 따른 디스플레이 변화 관련 함수들
    glutTimerFunc(0,C_Timer,0);
    glutTimerFunc(0, P_Timer, 0);

    // 디스플레이 화면 크기 변경에 관한 함수
    glutReshapeFunc(changesize);

    // 디스플레이 화면 구현에 관한 함수
    glutDisplayFunc(coordinatesystem);

    // 마우스 움직임 함수들
    glutMouseFunc(mouse_click);
    glutMotionFunc(mouse_move);
    glutMouseWheelFunc(mouse_wheel);

    glutMainLoop();
    return 0;
}