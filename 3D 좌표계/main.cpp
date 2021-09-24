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

float a_angle = 45.0, b_angle = 45.0, ratio;
float radius = 10.0f;
float la_angle = -145.0, lb_angle = -135.0, lradius = 1.0f;

int WIDTH = 400, HEIGHT = 400;

int Time = 10;

double mousePos[2];
double mouseMove[2];
int drag;

void Timer(int value) {
    if (a_angle >= 360) {
        a_angle -= 360;
    }
    if (b_angle >= 360) {
        b_angle -= 360;
    }
    if (la_angle >= 360) {
        la_angle -= 360;
    }
    if (lb_angle >= 360) {
        lb_angle -= 360;
    }
    GLdouble C_X = radius * cos(b_angle) * cos(a_angle);
    GLdouble C_Y = radius * cos(b_angle) * sin(a_angle);
    GLdouble C_Z = radius * sin(b_angle);
    GLdouble L_X = lradius * cos(lb_angle) * cos(la_angle);
    GLdouble L_Y = lradius * cos(lb_angle) * sin(la_angle);
    GLdouble L_Z = lradius * sin(lb_angle);
    glLoadIdentity();
    gluLookAt(C_X, C_Y, C_Z, -C_X + L_X, -C_Y + L_Y, -C_Z + L_Z, 0.0f, 0.0f, 1.0f);
    glutPostRedisplay();
    glutTimerFunc(Time, Timer, 0);
}

void changesize(int w, int h)
{
    // 창이 너무 작아졌을때 0 으로 나뉘는 것을 방지합니다.
    if (h == 0)
        h = 1;

    ratio = 1.0f * w / h;
    // 좌표계를 수정하기 전에 초기화합니다.
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // 뷰포트를 창 전체크기로 설정합니다. 
    glViewport(0, 0, w, h);
    GLdouble C_X = radius * cos(b_angle) * cos(a_angle);
    GLdouble C_Y = radius * cos(b_angle) * sin(a_angle);
    GLdouble C_Z = radius * sin(b_angle);
    GLdouble L_X = lradius * cos(lb_angle) * cos(la_angle);
    GLdouble L_Y = lradius * cos(lb_angle) * sin(la_angle);
    GLdouble L_Z = lradius * sin(lb_angle);

    // 절단 공간을 설정합니다.
    gluPerspective(60, ratio, 1, 1000);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(C_X, C_Y, C_Z, -C_X + L_X, -C_Y + L_Y, -C_Z+L_Z, 0.0f, 0.0f, 1.0f);
}

void mouse_click(int button, int state, int x, int y) {
    switch (button) {
    case GLUT_LEFT_BUTTON:
        if (state == GLUT_DOWN) {
            drag = 1;
            mousePos[0] = (double)(x-WIDTH/2)*2/WIDTH;
            mousePos[1] = (double)(y-HEIGHT/2)*2/HEIGHT;

        }
        break;
    case GLUT_RIGHT_BUTTON:
        if (state == GLUT_DOWN) {
            drag = 2;
            mousePos[0] = x;
            mousePos[1] = y;
        }
        break;
    }
}
void mouse_move(int x, int y) {
    if (drag != NULL) {
        mouseMove[0] = (double)(x-WIDTH/2)*2/WIDTH - mousePos[0];
        mouseMove[1] = (double)(y-HEIGHT/2)*2/HEIGHT - mousePos[1];

        a_angle += atan2(mouseMove[0], radius)/(3.14);
        b_angle -= atan2(mouseMove[1], radius) / (3.14);
        if (drag == 2) {
            la_angle += atan2(mouseMove[0], lradius) / (3.14);
            lb_angle -= atan2(mouseMove[1], lradius) / (3.14);
        }
    }
}

void mouse_wheel(int button, int dir, int x, int y) {
    if (dir > 0) {
        radius = radius / 2;
    }
    else {
        radius = radius * 2;
    }
    return;
}

void drawBitmapText(char* str, float x, float y, float z)
{
    glRasterPos3f(x, y, z); //문자열이 그려질 위치 지정

    while (*str)
    {
        //GLUT_BITMAP_TIMES_ROMAN_24 폰트를 사용하여 문자열을 그린다.
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *str);

        str++;
    }
}

void renderScene(void)
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
        glBegin(GL_LINES);
        glVertex3f(-100, -100 + num, 0);
        glVertex3f(100, -100 + num, 0);
        glVertex3f(-100 + num, -100, 0);
        glVertex3f(-100 + num, 100, 0);
        glEnd();
        num += 1;
    }
    char* arr[3][2] = { {"+X","-X"},{"+Y","-Y"},{"+Z","-Z"} };
    float matrix[3][3] = { {1,0,0},{0,1,0},{0,0,1} };
    for (int i = 0; i <= 2; i++) {
        glColor3f(1.0f, 0.0f, 0.0f);
        glBegin(GL_LINES);
        glVertex3f(5.0 * matrix[i][0], 5.0 * matrix[i][1], 5.0 * matrix[i][2]);
        glVertex3f(-5.0 * matrix[i][0], -5.0 * matrix[i][1], -5.0 * matrix[i][2]);
        glEnd();
        drawBitmapText(arr[i][0], 5.0 * matrix[i][0], 5.0 * matrix[i][1], 5.0 * matrix[i][2]);
        drawBitmapText(arr[i][1], -5.0 * matrix[i][0], -5.0 * matrix[i][1], -5.0 * matrix[i][2]);
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

    glutTimerFunc(0,Timer,0);
    glutReshapeFunc(changesize);
    glutDisplayFunc(renderScene);
    glutMouseFunc(mouse_click);
    glutMotionFunc(mouse_move);
    glutMouseWheelFunc(mouse_wheel);
    glutMainLoop();
    return 0;
}