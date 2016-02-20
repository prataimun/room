#include <GL/freeglut.h>  // GLUT, includes glu.h and gl.h
#include "world.h"

static World world;

void idle() {
    world.idle();
}

void display() {
    world.display();
}

void reshape(int w, int h) {
    world.reshape(w, h);
}

void keyDown(unsigned char key, int x, int y) {
    world.keyDown(key, x, y);
}

void keyUp(unsigned char key, int x, int y) {
    world.keyUp(key, x, y);
}

void mouseClick(int button, int state, int x, int y) {
    world.mouseClick(button, state, x, y);
}

void mouseMotion(int x, int y) {
    world.mouseMotion(x, y);
}

int main(int argc, char* argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_FLAT);
    world.init();
    glutIdleFunc(idle);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyDown);
    glutKeyboardUpFunc(keyUp);
    glutMouseFunc(mouseClick);
    glutPassiveMotionFunc(mouseMotion);
    /*void glutMouseFunc(void (*func)(int button, int state,
                                int x, int y));*/
    /*void glutPassiveMotionFunc(void (*func)(int x, int y));*/
    /*void glutSetCursor(GLUT_CURSOR_NONE);*/
    /* glutWarpPointer(middleX, middleY);*/
    glutMainLoop();
    return 0;
}
