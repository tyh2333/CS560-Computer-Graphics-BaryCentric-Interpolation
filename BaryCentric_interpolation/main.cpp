#include <GLUT/glut.h>
#include "basic.h"
#include "object.h"
#include <cstdlib>
#define TEAPOT 1
#define FLOWER 2
#define ROBOT 3
#define CAR 4
/// total rotate angle for flower.bmp, default : 360 degree
int rotate_angle_total = 360;
int WIDTH = 0, HEIGHT = 0;
Object teapot;
Object robot;
Object car;
int rotate_x = 0;
int rotate_y = 0;
float zoom = 1;
bool clicked = false;
int x_current = 0;
int y_current = 0;
int mode = 2;
Flower flower;
bool keys[100];
void mouse(int button, int state, int x, int y){
    if(button == GLUT_LEFT_BUTTON
       && state == GLUT_DOWN
       && !clicked
       && (mode == TEAPOT || mode == ROBOT || mode == CAR)){
        clicked = true;
        x_current = x;
        y_current = y;
    }
    else if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && !clicked && mode == FLOWER){
        clicked = true; 
        flower.current_click_point(Point(x, y));
    }
    else if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && clicked)
        clicked = false;
}

/// For : void glutPassiveMotionFunc(void (*func)(int x, int y))
/// when mouse moving in the window.
void move(int x, int y){
    /// For .bmp
    if(clicked && mode == FLOWER){
        flower.current_click_point(Point(x, y));
    }
    /// For .obj
    else if(clicked && (mode == TEAPOT || mode == ROBOT || mode == CAR)){
        rotate_x = (x - x_current);
        rotate_y = (y - y_current);
    }
}
/// Execute when press keys
void key(unsigned char key, int x, int y){
    if(key == 'f')
        mode = FLOWER;
    if(key == 't')
        mode = TEAPOT;
    if(key == 'b')
        mode = ROBOT;
    if(key == 'c')
        mode = CAR;
    keys[key] = true;
}
/// Execute when release keys
void key_up(unsigned char key, int x, int y){
    keys[key] = false;
}

void MenuItemClicked(int Value){
    switch(Value){
        case 1:
            exit(1);
    }
}

void CreateMenu(void){
    glutCreateMenu(MenuItemClicked);
    glutAddMenuEntry("exit", 1);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}
void display() {
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f );
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    if(mode == TEAPOT){
        glColor3f(1,1,1);
        if(keys['i'])
            zoom += 0.1;
        if(keys['o'])
            zoom -= 0.1;

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(60, 1, 1, 500000);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        gluLookAt(0,0,10,0,0,0,0,1,0);

        glRotatef(rotate_x, 0, 1, 0);
        glRotatef(rotate_y, 1, 0, 0);
        glScalef(zoom, zoom, zoom);
        teapot.draw();
    }
    else if(mode == CAR){
        glColor3f(1,1,1);
        if(keys['i'])
            zoom += 0.1;
        if(keys['o'])
            zoom -= 0.1;

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(60, 1, 1, 500000);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        gluLookAt(0,0,200,0,0,0,0,1,0);

        glRotatef(rotate_x, 0, 1, 0);
        glRotatef(rotate_y, 1, 0, 0);
        glScalef(zoom, zoom, zoom);
        car.draw();
    }
    else if(mode == ROBOT){
        glColor3f(1,1,1);
        if(keys['i'])
            zoom += 0.1;
        if(keys['o'])
            zoom -= 0.1;

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(60, 1, 1, 500000);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        gluLookAt(50,0,50,0,0,0,0,1,0);

        glRotatef(rotate_x, 0, 1, 0);
        glRotatef(rotate_y, 1, 0, 0);
        glScalef(zoom, zoom, zoom);
        robot.draw();
    }
    else if(mode == FLOWER){
        glMatrixMode( GL_PROJECTION );
        glLoadIdentity();
        gluOrtho2D( 0.0, WIDTH, HEIGHT,0.0 );
        flower.draw();
        glColor3f(1,0,0);
    }
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    WIDTH = w;
    HEIGHT = h;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-1.0, 1.0, -1.0, 1.0, 1.5, 200.0);
    glMatrixMode(GL_MODELVIEW);
}

void timerFunc(int){
    glutSwapBuffers();
    /// glutPostRedisplay mark current window needed to be redraw.
    /// redraw : next cycle in glutMainLoop

    // += 30 degree, and total degree
    if(flower.rot < rotate_angle_total)
    {
        flower.rot += 30;
        for(Triangle& t: flower.triangles) {
            t.rot += 30;
        }
    }
    glutPostRedisplay();
    glutTimerFunc(33, timerFunc, 1);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("tyh_assignment4");
    glClearColor(0.0, 0.0, 0.0, 0.0);
    CreateMenu();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(key);
    glutMouseFunc(mouse);
    glutPassiveMotionFunc(move);
    glutKeyboardUpFunc(key_up);
    teapot.read("./pic/teapot.obj");
    robot.read("./pic/robot.obj");
    car.read("./pic/car.obj");
    glutTimerFunc(33, timerFunc, 1);
    glutMainLoop();
}
