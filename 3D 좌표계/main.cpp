#include <gl/freeglut.h>
#include <math.h>
#include <gl\glut.h>
#include <gl\gl.h>
#include <gl\glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "Equation.h"
#include "particle.h"
#include "option.h"
#include "physics.h"

# define M_PI           3.14159265358979323846

using std::cout; 
using std::endl; 


Equation E = Equation();
Particle Pa = Particle();
Physics P = Physics();
Option O = Option();

// ����ǥ��
double camera[3] = { 10.0f,0,M_PI/6 }; // ī�޶��� �� ��ǥ�� { ������ , ZX ��� ����, Y �� ����}

// ���� ��ǥ��
double CX[3];                           // CX : ī�޶� ��ġ�� ���� ��ǥ��
double Up[3];      // ī�޶� ����� ���� ��ǥ��
double CY[3] = { 0,0,0 };               // ī�޶� ������ ���� ��ǥ��

// ���콺�� ���� ǥ��
int drag;   // drag 0 : �ƹ��͵� ������ ���� ����
            // drag 1 : ���콺 ���� Ű�� ���� ����
            // drag 2 : ���콺 ������ Ű�� ���� ����

// ������ �������� ���콺 ��ġ �� �̵� �ݰ� ����
double mousePos[3];
double P_mousePos[3];
double mouseMove[3];

// ������ â�� ũ��
int WIDTH = 400, HEIGHT = 400;
int P_WIDTH, P_HEIGHT;

double ratio[2];
int WIN[2];

bool pick = FALSE;
bool YPOS[8];
int numb;

// OpenGL Timer �Լ� ����
int Time = 10;

void picking() {
    double POS[3];
    double Ratio[2];
    double Win[2];
    double seq;
    double dis[8];
    double Dis[8];
    double min;
    for (int i = 0; i < Pa.num; i++) {
        for (int j = 0; j <= 2; j++) {
            POS[j] = Pa.particle[i][0][j];
        }
        E.Cubetoplane_1(CX, CY, POS, Ratio);
        E.Cubetoplane_2(Ratio, P_WIDTH, WIDTH, P_HEIGHT, HEIGHT, Win);
        dis[i] = sqrt(pow(Pa.particle[i][0][0] - (CX[0] + CY[0]), 2) + pow(Pa.particle[i][0][1] - (CX[1] + CY[1]), 2) + pow(Pa.particle[i][0][2] - (CX[2] + CY[2]), 2));
        if (sqrt(pow(WIN[0] - Win[0], 2) + pow(WIN[1] - Win[1], 2)) <= 10) {
            YPOS[i] = TRUE;

            cout << i << endl;
        }
        else {
            YPOS[i] = FALSE;
        }
    }
    for (int i = 0; i < Pa.num; i++) {
        if (YPOS[i] == TRUE) {
            min = dis[i];
            break;
        }
    }
    for (int i = 0; i < Pa.num; i++) {
        if (YPOS[i] == TRUE) {
            if (min > dis[i]) {
                min = dis[i];
            }
        }
    }

    for (int i = 0; i < Pa.num; i++) {
        if (YPOS[i] == TRUE) {
            if (dis[i] == min) {
                numb = i;
            }
            else {
                YPOS[i] = FALSE;
            }
        }
    }
}

void C_Timer(int value) {
    E.calculate(camera, CX);
    E.Upvector(CX, Up);
    glLoadIdentity();
    gluLookAt(CX[0] + CY[0],CX[1] + CY[1],CX[2] + CY[2],CY[0] , CY[1] , CY[2], Up[0], Up[1], Up[2]);
    glutPostRedisplay();
    glutTimerFunc(Time, C_Timer, 0);
    if (drag == 1) {
        double P_WIN[2];
        double pos[3] = { -4,3,-3 };
        E.Cubetoplane_1(CX, CY, pos, ratio);
        E.Cubetoplane_2(ratio, P_WIDTH, WIDTH, P_HEIGHT, HEIGHT, P_WIN);
        cout << "������â ��ǥ" << endl;
        cout << WIN[0] << "," << WIN[1] << endl;
        cout << "��ü�� ��ǥ" << endl;
        cout << P_WIN[0] << "," << P_WIN[1] << endl;
    }
}

void Timer(int value) {
    P.S_Force(Pa.particle);
    for (int i = 0; i < Pa.num; i++) {
        P.G_Force(i, Pa.particle);
        P.D_Force(i, Pa.particle);
        P.Contact(i, Pa.particle);
        P.E_Velocity(i, Pa.particle);
        P.Collision(i, Pa.particle);

        if (pick == TRUE&& drag==1) {
            if (YPOS[i] == TRUE) {
                for (int i = 0; i <= 2; i++) {
                    Pa.particle[numb][0][i] += mouseMove[i] * 0.05;
                }
            }
            else{
                for (int j = 0; j <= 2; j++) {
                    Pa.particle[i][0][j] += Pa.particle[i][1][j] * (float)P.Time / 1000;
                }
            }
        }
        else {
            for (int j = 0; j <= 2; j++) {
                Pa.particle[i][0][j] += Pa.particle[i][1][j] * (float)P.Time / 1000;
            }
        }
    }
    O.reset(Pa.particle);
    glutPostRedisplay();
    glutTimerFunc(P.Time, Timer, 1);
}

void changesize(int w, int h)
{
    // â�� �ʹ� �۾������� 0 ���� ������ ���� �����մϴ�.
    if (h == 0) {
        h = 1;
    }
    if (w == 0) {
        w = 1;
    }
    P_WIDTH = w;
    P_HEIGHT = h;

    double ratio = 1.0f * w / h;
    // ��ǥ�踦 �����ϱ� ���� �ʱ�ȭ�մϴ�.
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // ����Ʈ�� â ��üũ��� �����մϴ�. 
    glViewport(0, 0, w, h);

    // ���� ������ �����մϴ�.
    glFrustum(-(GLdouble)w/WIDTH, (GLdouble)w/WIDTH, -(GLdouble)h/HEIGHT, (GLdouble)h/HEIGHT, 1.0f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(CX[0] + CY[0], CX[1] + CY[1], CX[2] + CY[2], CY[0], CY[1], CY[2], Up[0], Up[1], Up[2]);
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 32:
        if (pick == FALSE) {
            pick = TRUE;
        }
        else {
            pick = FALSE;
        }
        break;
    case 'w':
        CY[1] += 0.025;
        cout << "���" << endl;
        break;
    case 's':
        CY[1] -= 0.025;

        cout << "�ϰ�" << endl;
        break;
    }
}

void mouse_click(int button, int state, int x, int y) {
    WIN[0] = x;
    WIN[1] = y;
    if (state == GLUT_DOWN) {
        switch(button) {
            case GLUT_LEFT_BUTTON:
                drag = 1;
                E.Planetovector(CX, CY, WIN, mousePos, P_WIDTH, P_HEIGHT);
                if (pick == TRUE) {
                    picking();
                }
                break;
            case GLUT_RIGHT_BUTTON:
                drag = 2;
                E.Planetovector(CX, CY, WIN, mousePos, P_WIDTH, P_HEIGHT);
                break;
        }
    }
    else {
        drag = 0;
    }
}
void mouse_move(int x, int y) {
    WIN[0] = x;
    WIN[1] = y;
    switch (drag) {
    case 1:
        E.Planetovector(CX, CY, WIN, P_mousePos, P_WIDTH, P_HEIGHT);
        for (int i = 0; i <= 2; i++) {
            mouseMove[i] = P_mousePos[i] - mousePos[i];
            P_mousePos[i] = mousePos[i];
        }
        if (pick == FALSE) {
            E.Rotate(camera, mouseMove);
        }
        break;
    case 2:
        if (pick == FALSE) {
            E.Planetovector(CX, CY, WIN, P_mousePos, P_WIDTH, P_HEIGHT);
            for (int i = 0; i <= 2; i++) {
                mouseMove[i] = P_mousePos[i] - mousePos[i];
                P_mousePos[i] = mousePos[i];
                if (i == 0) {
                    CY[i] += mouseMove[i] * 0.2;
                }
                else if (i == 2) {
                    CY[i] += mouseMove[i] * 0.2;
                }
            }
        }
        break;
    }

}

void mouse_wheel(int button, int dir, int x, int y) {
    if (dir > 0) {
        camera[0] -= camera[0]*0.03;
    }
    else {
        camera[0] += camera[0] *0.03;
    }
    return;
}

void coordinatesystem(void) // 
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // ������ �׸��ϴ�.
    glColor4f(0.2f, 0.2f, 0.2f, 0.2f);
    glBegin(GL_QUADS);
    glVertex3f(-100.0f, 0.0f, -100.0f);
    glVertex3f(-100.0f, 0, 100.0f);
    glVertex3f(100.0f, 0.0f, 100.0f);
    glVertex3f(100.0f, 0.0f, -100.0f);
    glEnd();

    float num = 0;
    while (num <= 200) {
        glColor3f(0.0f, 0.0f, 0.0f);
        glBegin(GL_LINES);
        glVertex3f(-100, 0, -100 + num);
        glVertex3f(100, 0, -100 + num);
        glVertex3f(-100 + num, 0, -100);
        glVertex3f(-100 + num, 0, 100);
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

    for (int i = 0; i < Pa.num; i++) {
        glPushName(i);
        glPushMatrix();
        glPointSize(10);
        glBegin(GL_POINTS);
        if (i == 6) {
            glColor3f(1.0, 0.0, 0.0);
        }
        else {
            glColor3f(1.0, 1.0, 0.0);
        }
        glVertex3f(Pa.particle[i][0][0], Pa.particle[i][0][1], Pa.particle[i][0][2]);
        glPopMatrix();
        glPopName();
        glEnd();
    }

    glColor4f(0.5, 0.5, 0.0,0.2);
    glLineWidth(1);
    glBegin(GL_LINES);
    {for (int i = 0; i < Pa.num - 1; i++) {
        for (int j = i + 1; j < Pa.num; j++) {
            glVertex3f(Pa.particle[i][0][0], Pa.particle[i][0][1], Pa.particle[i][0][2]);
            glVertex3f(Pa.particle[j][0][0], Pa.particle[j][0][1], Pa.particle[j][0][2]);
        }
    }}
    glEnd();

    glFlush();
    glutSwapBuffers();
}

int main(int argc, char** argv)
{
    O.start(Pa.particle);
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow("3D Coordinate System");
    glClearColor(0.0, 0.0, 0.0, 0.5);
    
    // �ð��� ���� ���÷��� ��ȭ ���� �Լ���
    glutTimerFunc(0,C_Timer,0);
    glutTimerFunc(0, Timer, 0);

    // ���÷��� ȭ�� ũ�� ���濡 ���� �Լ�
    glutReshapeFunc(changesize);

    // ���÷��� ȭ�� ������ ���� �Լ�
    glutDisplayFunc(coordinatesystem);

    // Ű���� �Լ���
    glutKeyboardFunc(keyboard);

    // ���콺 ������ �Լ���
    glutMouseFunc(mouse_click);
    glutMotionFunc(mouse_move);
    glutMouseWheelFunc(mouse_wheel);

    glutMainLoop();
    return 0;
}