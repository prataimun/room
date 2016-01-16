/*
 * room.cpp: Test OpenGL C/C++ Setup
 */

#include <GL/freeglut.h>  // GLUT, includes glu.h and gl.h

static int year = 0, day = 0, angle = 0;

void init(void) 
{
   glClearColor (0.0, 0.0, 0.0, 0.0);
   glShadeModel (GL_FLAT);
}

void display(void)
{
   glClear (GL_COLOR_BUFFER_BIT);
   glColor3f (1.0, 1.0, 1.0);

   glPushMatrix();
   glRotatef ((GLfloat) angle, 1.0, 0.0, 0.0);
   glutWireSphere(1.0, 20, 16);   /* draw sun */
   glRotatef ((GLfloat) year, 0.0, 1.0, 0.0);
   glTranslatef (2.0, 0.0, 0.0);
   glRotatef ((GLfloat) day, 0.0, 1.0, 0.0);
   glutWireSphere(0.2, 10, 8);    /* draw smaller planet */
   glPopMatrix();
   glutSwapBuffers();
}

void reshape (int w, int h)
{
   glViewport (0, 0, (GLsizei) w, (GLsizei) h); 
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();
   gluPerspective(60.0, (GLfloat) w/(GLfloat) h, 1.0, 20.0);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   gluLookAt (0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

void keyboard (unsigned char key, int x, int y) {
    switch (key) {
    case 'w':
        day = (day + 10) % 360;
        glutPostRedisplay();
        break;
    case 'W':
        day = (day - 10) % 360;
        glutPostRedisplay();
        break;
    case 'a':
        year = (year + 5) % 360;
        glutPostRedisplay();
        break;
    case 'A':
        year = (year - 5) % 360;
        glutPostRedisplay();
        break;
    case 'd':
        angle = (angle + 5) % 360;
        glutPostRedisplay();
        break;
    case 'D':
        angle = (angle - 5) % 360;
        glutPostRedisplay();
        break;
    case 's':
        day = (day + 10) % 360;
        year = (year + 5) % 360;
        angle = (angle + 5) % 360;
        glutPostRedisplay();
        break;
    case 'S':
        day = (day - 10) % 360;
        year = (year - 5) % 360;
        angle = (angle - 5) % 360;
        glutPostRedisplay();
        break;
    default:
         break;
    }
}

void start(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize (500, 500); 
    glutInitWindowPosition (100, 100);
    glutCreateWindow (argv[0]);
    init ();
    glutDisplayFunc(display); 
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
}

