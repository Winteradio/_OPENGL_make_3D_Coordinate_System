#include <gl/freeglut.h>
#include <iostream>

//����� ���̺귯���� �������ݴϴ�.
#pragma comment(lib, "freeglut.lib")
#pragma comment(lib, "glew32s.lib")

using namespace std;

//ȸ��
float pitch = 0.0;
float yaw = 0.0;
float roll = 0.0;

void drawBitmapText(char* str, float x, float y, float z)
{
    glRasterPos3f(x, y, z); //���ڿ��� �׷��� ��ġ ����

    while (*str)
    {
        //GLUT_BITMAP_TIMES_ROMAN_24 ��Ʈ�� ����Ͽ� ���ڿ��� �׸���.
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *str);

        str++;
    }
}

void draw_line()
{
    glPushMatrix();

    glPushMatrix(); 
    glLineWidth(2);
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_LINES);
    glVertex3f(1.0, 0.0, 0.0);
    glVertex3f(-1.0, 0.0, 0.0);
    glEnd();
    drawBitmapText("+X", 0.8, 0.0, 0.0);
    drawBitmapText("-X", -0.8, 0.0, 0.0);
    glPopMatrix();

    glPushMatrix();
    glLineWidth(2);
    glColor3f(1.0,0.0, 0.0);
    glBegin(GL_LINES);
    glVertex3f(0.0, 1.0, 0.0);
    glVertex3f(0.0, -1.0, 0.0);
    glEnd();
    drawBitmapText("+Y", 0.0, 0.8, 0.0);
    drawBitmapText("-Y", 0.0, -0.8, 0.0);
    glPopMatrix();

    glPushMatrix(); 
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_LINES);
    glVertex3f(0.0, 0.0, 1.0);
    glVertex3f(0.0, 0.0, -1.0);
    glEnd();
    drawBitmapText("+Z", 0.0, 0.0, 0.8);
    drawBitmapText("-Z", 0.0, 0.0, -0.8);
    glPopMatrix();

    glPushMatrix();
    glLineWidth(1);
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_LINES);
    {
        float num = 0;
        while (num <= 40) {
            glVertex3f(-10, -10+ num, 0);
            glVertex3f(10, -10 + num, 0);
            glVertex3f(-10 + num,-10, 0);
            glVertex3f(-10 + num, 10, 0);
            num += 0.2;
        }
    }
    glEnd();
    glPopMatrix();

    glPopMatrix();

    glFlush();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //���� ������ ModelView Matirx�� ������ �ش�. ��ü ����
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glRotatef(pitch, 1.0, 0.0, 0.0); //x�࿡ ���� ȸ��
    glRotatef(yaw, 0.0, 1.0, 0.0); //y�࿡ ���� ȸ��
    glRotatef(roll, 0.0, 0.0, 1.0); //z�࿡ ���� ȸ��

    draw_line();

    glutSwapBuffers();
}

void timer(int value) {
    glutPostRedisplay();      //�����츦 �ٽ� �׸����� ��û
    glutTimerFunc(30, timer, 0); //���� Ÿ�̸� �̺�Ʈ�� 30�и�����Ʈ ��  ȣ���.
}



void init()
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClearDepth(1.0);

    glEnable(GL_DEPTH_TEST);
}

void special(int key, int x, int y)
{
    if (key == GLUT_KEY_UP)
    {
        pitch += 1.0;
    }
    else if (key == GLUT_KEY_DOWN)
    {
        pitch -= 1.0;
    }
    else if (key == GLUT_KEY_RIGHT)
    {
        yaw += 1.0;
    }
    else if (key == GLUT_KEY_LEFT)
    {
        yaw -= 1.0;
    }
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);  //GLUT �ʱ�ȭ

    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH); //���� ���ۿ� ���� ���۸� ����ϵ��� ����, GLUT_RGB=0x00��
    glutInitWindowSize(500, 500);   //�������� width�� height
    glutInitWindowPosition(100, 100); //�������� ��ġ (x,y)
    glutCreateWindow("OpenGL Example"); //������ ����


    init();

    glutDisplayFunc(display);
 
    glutSpecialFunc(special);

    glutTimerFunc(0, timer, 0);

    glutMainLoop();

    return 0;
}

