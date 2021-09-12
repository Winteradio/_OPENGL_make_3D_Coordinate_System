#include <gl/freeglut.h>
#include <iostream>

//사용할 라이브러리를 지정해줍니다.
#pragma comment(lib, "freeglut.lib")
#pragma comment(lib, "glew32s.lib")

using namespace std;

//회전
float pitch = 0.0;
float yaw = 0.0;
float roll = 0.0;

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

    //이후 연산은 ModelView Matirx에 영향을 준다. 객체 조작
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glRotatef(pitch, 1.0, 0.0, 0.0); //x축에 대해 회전
    glRotatef(yaw, 0.0, 1.0, 0.0); //y축에 대해 회전
    glRotatef(roll, 0.0, 0.0, 1.0); //z축에 대해 회전

    draw_line();

    glutSwapBuffers();
}

void timer(int value) {
    glutPostRedisplay();      //윈도우를 다시 그리도록 요청
    glutTimerFunc(30, timer, 0); //다음 타이머 이벤트는 30밀리세컨트 후  호출됨.
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
    glutInit(&argc, argv);  //GLUT 초기화

    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH); //더블 버퍼와 깊이 버퍼를 사용하도록 설정, GLUT_RGB=0x00임
    glutInitWindowSize(500, 500);   //윈도우의 width와 height
    glutInitWindowPosition(100, 100); //윈도우의 위치 (x,y)
    glutCreateWindow("OpenGL Example"); //윈도우 생성


    init();

    glutDisplayFunc(display);
 
    glutSpecialFunc(special);

    glutTimerFunc(0, timer, 0);

    glutMainLoop();

    return 0;
}

