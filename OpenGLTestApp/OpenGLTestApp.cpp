#define FREEGLUT_STATIC

#ifdef __APPLE_CC__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
static int rotateAngle = 0;

void special(int key, int, int) {
    switch (key) {
    case GLUT_KEY_LEFT: (rotateAngle += 5) %= 360; break;
    case GLUT_KEY_RIGHT: (rotateAngle -= 5) %= 360; break;
    default: return;
    }
    glutPostRedisplay();
}

void display() {

    glClear(GL_COLOR_BUFFER_BIT);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    glEnable(GL_LINE_SMOOTH);
    glLineWidth(2);

    glColor3f(1.0, 1.0, 1.0);
  
    glRotatef((GLfloat)rotateAngle, 0.0, 1.0, 0.0);
    glBegin(GL_LINES);
    glColor3f(1, 0, 0); glVertex3f(0, 0, 0); glVertex3f(10, 0, 0);
    glColor3f(0, 1, 0); glVertex3f(0, 0, 0); glVertex3f(0, 10, 0);
    glColor3f(0, 1, 0); glVertex3f(0, 0, 0); glVertex3f(10, 10, 0);
    glColor3f(0, 1, 0); glVertex3f(0, 0, 0); glVertex3f(0, 10, 10);
    glColor3f(0, 0, 1); glVertex3f(0, 0, 0); glVertex3f(0, 0, 10);
    glEnd();

    glFlush();
}

// Sets up global attributes like clear color and drawing color, and sets up
// the desired projection and modelview matrices.
void init() {

    // Set the current clear color to black and the current drawing color to
    // white.
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glColor3f(1.0, 1.0, 1.0);

    // Set the camera lens to have a 60 degree (vertical) field of view, an
    // aspect ratio of 4/3, and have everything closer than 1 unit to the
    // camera and greater than 40 units distant clipped away.
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, 4.0 / 3.0, 1, 40);

    // Position camera at (4, 6, 5) looking at (0, 0, 0) with the vector
    // <0, 1, 0> pointing upward.
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(4, 6, 5, 0, 0, 0, 0, 1, 0);
}

// Initializes GLUT, the display mode, and main window; registers callbacks;
// does application initialization; enters the main event loop.
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(80, 80);
    glutInitWindowSize(800, 600);
    glutCreateWindow("AMD line smooth test");
    glutDisplayFunc(display);
    glutSpecialFunc(special);
    init();
    glutMainLoop();
}