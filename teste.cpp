#include <GL/glut.h>
#include <iostream>

// window size
#define lenX 500
#define lenY 500

// colors
#define red 1.0, 0.0, 0.0
#define white 1.0, 1.0, 1.0
#define blue 0.0, 0.0, 1.0
#define green 0.0, 1.0, 0.0
#define black 0.0, 0.0, 0.0
#define grey 0.6, 0.6, 0.6


// variables
double xBody = 0.0;
double yBody = 0.0;
double sxy = 1.0;
double ra = 0.0;
double rfa = 0.0;
bool arm, armMax, forearm, forearmMax = false;

// prototypes
void drawBody();
void drawArm();
void drawForearm();
void drawShapes();
void reshape(int, int);
void keyboardActions(unsigned char, int, int);
//void specialKeyboardActions(int, int, int);



int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);

    glutInitWindowSize(lenX, lenY);
    glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH)-lenX)/2, (glutGet(GLUT_SCREEN_HEIGHT)-lenY)/2);
    glutCreateWindow("Just a Test");
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(white,1.0);

    glutDisplayFunc(drawShapes);
    glutReshapeFunc(reshape);
    //glutSpecialFunc(specialKeyboardActions);
    glutKeyboardFunc(keyboardActions);
    //glOrtho(0, lenX, 0, lenY, -1, 1);

    glutMainLoop();
}


void drawBody() {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glBegin(GL_QUADS);
        // Head
        glColor4f(grey,0.4);
		glVertex2d(xBody-5, yBody+10);
		glVertex2d(xBody-5, yBody-10);
        glColor4f(grey,1.0);
        glVertex2d(xBody-15, yBody-10);
		glVertex2d(xBody-15, yBody+10);

        // Shape
        glColor4f(grey,0.4);
		glVertex2d(xBody-7.5, yBody+15.5);
		glVertex2d(xBody-7.5, yBody+10.5);
        glColor4f(grey,1.0);
        glVertex2d(xBody-12.5, yBody+10.5);
		glVertex2d(xBody-12.5, yBody+15.5);
    glEnd();
}

void drawArm() {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glBegin(GL_POLYGON);
        glColor4f(grey,0.4);
		glVertex2d(xBody-2.5, yBody+10);
		glVertex2d(xBody-2.5, yBody+0);
        glColor4f(blue,1.0);
        glVertex2d(xBody-5, yBody+0);
		glVertex2d(xBody-5, yBody+10);
    glEnd();

}


void drawForearm() {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBegin(GL_POLYGON);
        glColor4f(grey,0.4);
		glVertex2d(xBody-2.5, yBody+0);
		glVertex2d(xBody-2.5, yBody-5);
        glColor4f(red,1.0);
        glVertex2d(xBody-5, yBody-5);
		glVertex2d(xBody-5, yBody+0);
    glEnd();
}


void drawShapes() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glPushMatrix();
            glScaled(sxy,sxy,1.0);

        glPushMatrix();
            glTranslated(xBody,yBody,0.0);
            drawBody();

            glPushMatrix();
                glTranslated(-3.75, 10.0, 0.0);
                glRotated(ra, 0.0, 0.0, 1.0);
                glTranslated(3.75, -10.0, 0.0);
                drawArm();

            //glPushMatrix();
                glTranslated(-3.75, 0.0, 0.0);
                glRotated(rfa, 0.0, 0.0, 1.0);
                glTranslated(3.75, 0.0, 0.0);
                drawForearm();
            //glPopMatrix();
            glPopMatrix();

        glPopMatrix();

    glPopMatrix();

    glutSwapBuffers();
}

void reshape(int x, int y) {
    glViewport(0, 0, x, y);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-20,20,-20,20);
    glMatrixMode(GL_MODELVIEW);
}

void keyboardActions(unsigned char key, int xM, int yM) {
    switch(key) {
        // translate
        case 'a':
            xBody -= 1;
            break;
        case 'w':
            yBody += 1;
            break;
        case 'd':
            xBody += 1;
            break;
        case 's':
            yBody -= 1;
            break;
        case 'A':
            xBody -= 1;
            break;
        case 'W':
            yBody += 1;
            break;
        case 'D':
            xBody += 1;
            break;
        case 'S':
            yBody -= 1;
            break;

        // scale
        case 'e':
            sxy -= 0.2;
            break;
        case 'E':
            sxy += 0.2;
            break;

        // rotate
        case 'r':
            forearm = true;
            if(forearmMax) {
                if(rfa > ra) {
                    rfa -= 10.0;
                } else {
                    forearmMax = false;
                }
            } else {
                if (rfa < 150) {
                    rfa += 10.0;
                } else {
                    forearmMax = true;
                }
            }
            break;
        case 'R':
            arm = true;
            if(armMax) {
                if(ra > 0) {
                    ra -= 10.0;
                } else {
                    armMax = false;
                }
            } else {
                if(ra < 190) {
                    ra += 10.0;
                } else {
                    armMax = true;
                }
            }
            break;
        default:
            break;
    }
    glutPostRedisplay();
}