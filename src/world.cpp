#include <GL/freeglut.h>  // GLUT, includes glu.h and gl.h
#include <iostream>
#include <ctime>
#include <map>
#include <math.h>
#include "world.h"
#include "person.h"

static int year = 0, day = 0, angle = 0;

void World::display(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3d(1.0, 1.0, 1.0);
    glPushMatrix();
    glRotated((GLdouble) angle, 1.0, 0.0, 0.0);
    glutWireSphere(1.0, 20, 16);   /* draw sun */
    glRotatef((GLdouble) year, 0.0, 1.0, 0.0);
    glTranslated(2.0, 0.0, 0.0);
    glRotatef((GLdouble) day, 0.0, 1.0, 0.0);
    glutWireSphere(0.2, 10, 8);    /* draw smaller planet */
    glPopMatrix();
    glutSwapBuffers();
}

void World::reshape(int w, int h) {
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (GLdouble) w/(GLdouble) h, 1.0, 20.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(victor.x, 0.0, victor.z, victor.x, 0.0, 0.0, 0.0, 1.0, 0.0);
}

void World::keyDown(unsigned char key, int x, int y) {
    switch (key) {
    case 'v':
        day = (day + 10) % 360;
        glutPostRedisplay();
        break;
    case 'V':
        day = (day - 10) % 360;
        glutPostRedisplay();
        break;
    case 'b':
        year = (year + 5) % 360;
        glutPostRedisplay();
        break;
    case 'B':
        year = (year - 5) % 360;
        glutPostRedisplay();
        break;
    case 'n':
        angle = (angle + 5) % 360;
        glutPostRedisplay();
        break;
    case 'N':
        angle = (angle - 5) % 360;
        glutPostRedisplay();
        break;
    case 'm':
        day = (day + 10) % 360;
        year = (year + 5) % 360;
        angle = (angle + 5) % 360;
        glutPostRedisplay();
        break;
    case 'M':
        day = (day - 10) % 360;
        year = (year - 5) % 360;
        angle = (angle - 5) % 360;
        glutPostRedisplay();
        break;
    default:
         break;
    }
    // sets the function corresponding to the keypress to be active
    if (controls.count(key) > 0) {
        controls[key].first = controls[key].second;
    }
}

void (*World::nullOperation)(double, Person *) = [] (double t, Person *p) {};

static void movePerson(Person *person) {
    glViewport(0, 0, 500, 500);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, 1.0, 0.9, 20.1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(person->x, person->y, person->z, person->x + person->xd, person->y + person->yd, person->z + person->zd, 0.0, 1.0, 0.0);
    glutPostRedisplay();
}

void World::init() {
    controls['w'] = std::make_pair(nullOperation,
            [] (double passed_time, Person *person) {person->moveForward(0.1); movePerson(person);});
    controls['a'] = std::make_pair(nullOperation,
            [] (double passed_time, Person *person) {person->strafeRight(-0.1); movePerson(person);});
    controls['s'] = std::make_pair(nullOperation,
            [] (double passed_time, Person *person) {person->moveForward(-0.1); movePerson(person);});
    controls['d'] = std::make_pair(nullOperation,
            [] (double passed_time, Person *person) {person->strafeRight(0.1); movePerson(person);});
    trackMouse = false;
    lastClock = clock();
}

void World::idle() {
    clock_t t = clock();
    double passedTime = ((double)(t - lastClock))/ (double) CLOCKS_PER_SEC;
    lastClock = t;
    /* calls each keys corresponding function, if the key is not pressed the
     * function will not do anything */
    for (auto it = controls.begin(); it != controls.end(); it++) {
        it->second.first(passedTime, &victor);
    }
}

void World::keyUp(unsigned char key, int x, int y) {
    if (controls.count(key) > 0) {
        controls[key].first = nullOperation;
    }
}

void World::mouseClick(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        trackMouse = !trackMouse;
        if (trackMouse) {
            glutSetCursor(GLUT_CURSOR_NONE);
            glutWarpPointer(250, 250);
        } else {
            glutSetCursor(GLUT_CURSOR_LEFT_ARROW);
        }
    }
}

void World::mouseMotion(int x, int y) {
    double xyDeg = (250.0 - y) / 10.0;
    double zxDeg = (250.0 - x) / 10.0;
    if (trackMouse && (xyDeg != 0 || zxDeg != 0)) {
        victor.rotateHorizontal(zxDeg);
        victor.rotateVertical(xyDeg);
        glutWarpPointer(250, 250);
        movePerson(&victor);
        glutPostRedisplay();
    }
}

