/**
* CMPS 160L (Fall 2011)
* Lab 2: Animated Animal
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <GLUT/glut.h>

#include "util.h"
// Global variables
float angle = 0;
static int shoulder = 0, elbow = 0;
bool is_spinning = false;
bool wireframe = false;

// Do spin
void spin() {
	if (is_spinning) {
		is_spinning = false;
		angle = 0.0;
	} else {
		is_spinning = true;
	}
}

void bananaBody(){
    glPushMatrix();
    glScalef(.1,.1,.1);
    
    if (wireframe){
        glPolygonMode(GL_FRONT, GL_LINE);
        glPolygonMode(GL_BACK, GL_LINE);
        glFrontFace(GL_CW);
    }
    else {
        glPolygonMode(GL_FRONT, GL_FILL);
        glPolygonMode(GL_BACK, GL_FILL);
    }
    
    //faces
    glColor3ub(245, 239, 37);
    glBegin(GL_TRIANGLE_STRIP);
        glVertex3f(0,0,-1);
        glVertex3f(1,2,0);
        glVertex3f(-1,2,0);
        //middle section
        glVertex3f(-1,5,0);
        glVertex3f(1,5,0);
        
        glVertex3f(1,2,0);
        //top
        glVertex3f(-1,5,0);
        glVertex3f(1,5,0);
        glVertex3f(0,7,-1);
    glEnd();
    
    glColor3ub(200, 100, 200);
    glBegin(GL_TRIANGLE_STRIP);
        glVertex3f(0,0,-1);
        glVertex3f(1,2,-1);
        glVertex3f(-1,2,-1);
        //middle section
        glVertex3f(-1,5,-1);
        glVertex3f(1,5,-1);
        
        glVertex3f(1,2,-1);
        //top
        glVertex3f(-1,5,-1);
        glVertex3f(1,5,-1);
        glVertex3f(0,7,-1);
    glEnd();
    
    glColor3ub(0, 0, 200);
    //Sides
    glBegin(GL_TRIANGLE_STRIP);
        glVertex3f(0,0,-1);
        glVertex3f(1,2,-1);
        glVertex3f(1,2,0);
        glVertex3f(1,5,-1);
        glVertex3f(1,5,0);
        glVertex3f(0,7,-1);
    glEnd();
    glColor3ub(100, 0, 100);
    glBegin(GL_TRIANGLE_STRIP);
        glVertex3f(0,0,-1);
        glVertex3f(-1,2,-1);
        glVertex3f(-1,2,0);
        glVertex3f(-1,5,-1);
        glVertex3f(-1,5,0);
        glVertex3f(0,7,-1);
    glEnd();
    glPopMatrix();
    
    
}
void body(){
    glColor3ub(245, 239, 37);
    glRotatef(90,1,0,0);
    glRotatef(20,0,1,0);
    
    glPushMatrix();
    float shear2[] = {
        1, 0, -.35, 0,
        0, 1, 0, 0,
       -0.35, 0, 1, 0,
        0, 0, 0, 1 };
    glMultMatrixf(shear2);
//
    
//    glRotatef(
    float shear[] = {
        1, 0, .35, 0,
        0, 1, 0, 0,
        0.35, 0, 1.3, 0,
        0, 0, 0, 1 };
    glMultMatrixf(shear);
    glutWireCone(1,3,4,5);
    glPopMatrix();
    
    glPushMatrix();
    float shear3[] = {
        1, 0, -.35, 0,
        0, 1, 0, 0,
        -0.35, 0, 1, 0,
        0, 0, 0, 1 };
    glMultMatrixf(shear3);
    //
    
    //    glRotatef(
    float shear4[] = {
        1, 0, .35, 0,
        0, 1, 0, 0,
        0.35, 0, -1, 0,
        0, 0, 0, 1 };
//    glRotatef(90,0,0,1);

    glMultMatrixf(shear4);
    glutWireCone(1,3,4,5);
    glPopMatrix();

    

}

void leg(){
    glRotatef(-90,0,0,1);
    glPushMatrix();
    glTranslatef (-1.0, 0.0, 0.0);
    glRotatef ((GLfloat) shoulder, 0.0, 0.0, 1.0);
    glTranslatef (1.0, 0.0, 0.0);
    glPushMatrix();
    glScalef (2.0, 0.4, 1.0);
    glColor3ub(20, 191, 183);
    
    glutSolidCube (1.0);
    glPopMatrix();
    
    glTranslatef (1.0, 0, 0.0);
    glRotatef(90,0,0,1);
    glRotatef ((GLfloat) elbow, 0.0, 0.0, 1.0);
    glTranslatef (0.5, 0.25, 0.0);
    glPushMatrix();
    glScalef (1.0, 0.4, .75);
    glColor3ub(191, 191, 183);
    glutSolidCube (1.0);
    glPopMatrix();

    glPopMatrix();
//    glutSwapBuffers();
}

void leftLeg(){
    glPushMatrix();
    glRotatef(10,0,1,0);
    glScalef(.8,1,1);
    leg();
    glPopMatrix();
}

void cb_display() {
    
    static clock_t previous_clock = 0;
    static clock_t ms_since_last = 0;
    clock_t now = clock() / (CLOCKS_PER_SEC / 1000);
    ms_since_last = now - previous_clock;
    if (ms_since_last < 20) {
        return;
    }
    previous_clock = now;
    
    
	glClear(GL_COLOR_BUFFER_BIT);

	glLoadIdentity();

	camera();

	// Rotate along y-axis
	if (is_spinning) {
		glRotatef(angle, 0, 1, 0);
		angle++;
	}

	draw_axis(4.0);

	glColor3f(1, 1, 1);
	//glutWireTeapot(2.0);
//	glutWireCube(1.0);
//    glScalef(1,1,2);
//    bananaBody();
//    leftLeg();
    glPushMatrix();
//    glScalef(4,4,4);
//    bananaBody();
    body();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-3,2,0);
    leftLeg();
    glPopMatrix();
	glFlush();
	glutSwapBuffers(); // for smoother animation
}

void cb_idle() {
	glutPostRedisplay();
}
void flipFrame(){
//    wireframe = !
}

void cb_keyboard(unsigned char key, int x, int y) {
	// Add controls to animation, joint movement control, etc.
	// Some camera functions are provided for model viewing convinience.
	switch(key) {
        case'w':
            wireframe = !wireframe;
            break;
        case'd':
            //duplicate();
            break;
		case '1':
			set_cam(DEFAULT);
			break;
		case '2':
			set_cam(FRONT);
			break;
		case '3':
			set_cam(SIDE);
			break;
		case '4':
			set_cam(TOP);
			break;
		case '5':
			set_cam(ANGLE);
			break;
		case 's':
			spin();
			break;
        case 't':
            shoulder = (shoulder + 5) % 360;
//            glutPostRedisplay();
            break;
        case 'T':
            shoulder = (shoulder - 5) % 360;
//            glutPostRedisplay();
            break;
        case 'e':  /*  e key rotates at elbow  */
            elbow = (elbow + 5) % 360;
//            glutPostRedisplay();
            break;
        case 'E':
            elbow = (elbow - 5) % 360;
//            glutPostRedisplay();
            break;
		case 'q':
			exit(0);
			break;
	}
}

void cb_reshape(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-1.0, 1.0, -1.0, 1.0, 1.0, 100.0);
	glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Lab 2: Robotic Animals");

	glutDisplayFunc(cb_display);
	glutReshapeFunc(cb_reshape);
	glutIdleFunc(cb_idle);
	glutKeyboardFunc(cb_keyboard);

	glClearColor(0,0,0,0); // set background to black

	glutMainLoop();

	return 0;
}