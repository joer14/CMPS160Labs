/**
* CMPS 160L (Fall 2013)
* Lab 2: Animated Animal
* Nick Dowse ndowse@ucsc.edu
* 1393177
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <GLUT/glut.h>
#include <math.h>
#include "util.h"

// Global variables
float spinAngle = 0;
float leftMoveAngle = 0;
float rightMoveAngle = 0;
bool is_spinning = false;
bool is_moving = false;
bool left_move_angle_increasing = true;
bool right_move_angle_increasing = false;
bool left_leg_moving = false;
bool right_leg_moving = false;
bool right_arm_moving = false;
bool left_arm_moving = false;
bool lower_left_leg_moving = false;
bool lower_right_leg_moving = false;
bool lower_right_arm_moving = false;
bool lower_left_arm_moving = false;
int duplicates = 1;

void updateLeftMoveAngle(){
	if (left_move_angle_increasing){
		if (leftMoveAngle > 45){
			left_move_angle_increasing = false;
			leftMoveAngle--;
		} else {
			leftMoveAngle++;
		}
	} else {
		if (leftMoveAngle < -45){
			left_move_angle_increasing = true;
			leftMoveAngle++;
		} else {
			leftMoveAngle--;
		}
	}
}

void updateRightMoveAngle(){
	if (right_move_angle_increasing){
		if (rightMoveAngle > 45){
			right_move_angle_increasing = false;
			rightMoveAngle--;
		} else {
			rightMoveAngle++;
		}
	} else {
		if (rightMoveAngle < -45){
			right_move_angle_increasing = true;
			rightMoveAngle++;
		} else {
			rightMoveAngle--;
		}
	}
}

void head(){
	glPushMatrix();
	glTranslatef(-0.5, 1.2, 0);
	glLineWidth(2.5);
	glColor3f(1.0, 0.0, 0.0);
	glTranslatef(-0.25, -0.3, 0.6); //mouth
	glBegin(GL_LINES);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.5, 0, 0);
	glEnd();
	glTranslatef(-0.25, 0.5, 0); // left eye
	glBegin(GL_LINES);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.25, 0, 0);
	glEnd();
	glTranslatef(0.75, 0, 0); // right eye
	glBegin(GL_LINES);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.25, 0, 0);
	glEnd();
	glColor3f(1.0, 1.0, 1.0);
	glTranslatef(-0.25, -0.25, -0.6);
	glutSolidCube(1.0); //head
	
	glPopMatrix();
}
void torso(){
	glColor3b(100,100, 100);
	glTranslatef(-1, 2, 0);
	glutSolidCube(1.0);
	glTranslatef(0, -1, 0);
	glutSolidCube(1.0);
	glTranslatef(1, 0, 0);
	glutSolidCube(1.0);
	glTranslatef(0, 1, 0);
	glutSolidCube(1.0);
}

void lowerLeftLimbRotate(){
	if (is_moving || left_leg_moving || lower_left_leg_moving){
		if (lower_left_leg_moving){
			if (leftMoveAngle > 0){
				glRotatef(leftMoveAngle, 1, 0, 0);
			} else {
				glRotatef(-leftMoveAngle, 1, 0, 0);
			}
		} else {
			if (leftMoveAngle > 0){
				glRotatef(leftMoveAngle, 1, 0, 0);
			} else {
				glRotatef(-leftMoveAngle, 1, 0, 0);
			}
		}
	}
}

void lowerRightLimbRotate(){
	if (is_moving || right_leg_moving || lower_right_leg_moving){
		if (lower_right_leg_moving){
			if (rightMoveAngle > 0){
				glRotatef(rightMoveAngle, 1, 0, 0);
			} else {
				glRotatef(-rightMoveAngle, 1, 0, 0);
			}
		} else {
			if (rightMoveAngle > 0){
				glRotatef(rightMoveAngle, 1, 0, 0);
			} else {
				glRotatef(-rightMoveAngle, 1, 0, 0);
			}
		}
	}
}

void upperLeftLimbRotate(){
	if (is_moving || left_arm_moving || lower_left_arm_moving){
		if (lower_left_arm_moving){
			if (leftMoveAngle > 0){
				glRotatef(-leftMoveAngle, 1, 0, 0);
			} else {
				glRotatef(leftMoveAngle, 1, 0, 0);
			}
		} else {
			if (leftMoveAngle > 0){
				glRotatef(-leftMoveAngle, 1, 0, 0);
			} else {
				glRotatef(leftMoveAngle, 1, 0, 0);
			}
		}
	}
}

void upperRightLimbRotate(){
	if (is_moving || right_arm_moving || lower_right_arm_moving){
		if (lower_right_arm_moving){
			if (rightMoveAngle > 0){
				glRotatef(-rightMoveAngle, 1, 0, 0);
			} else {
				glRotatef(rightMoveAngle, 1, 0, 0);
			}
		} else {
			if (rightMoveAngle > 0){
				glRotatef(-rightMoveAngle, 1, 0, 0);
			} else {
				glRotatef(rightMoveAngle, 1, 0, 0);
			}
		}
	}
}

void lowerLeftArm(){
	glTranslatef(0, -0.6, 0);
	glPushMatrix();
    upperLeftLimbRotate();
	glutSolidCube(0.5);
	glTranslatef(0, -0.5, 0);
	glutSolidCube(0.5);
	glPopMatrix();
}

void leftArm(){ //maroon arm
	glColor3b(23, 67, 12);
	glTranslatef(-2, 0, 0);
	glPushMatrix();
	if (is_moving || left_arm_moving){
		glRotatef(leftMoveAngle, 1, 0, 0);
	}
	glutSolidCube(0.5);
	glTranslatef(0, -0.5, 0);
	glutSolidCube(0.5);
	lowerLeftArm();
	glPopMatrix();
}

void lowerRightArm(){
	glTranslatef(0, -0.6, 0);
	glPushMatrix();
    upperRightLimbRotate();
	glutSolidCube(0.5);
	glTranslatef(0, -0.5, 0);
	glutSolidCube(0.5);
	glPopMatrix();
}

void rightArm(){ //pink arm
	glColor3b(123, 12, 67);
	glTranslatef(3, 0, 0);
	glPushMatrix();
	if (is_moving || right_arm_moving){
		glRotatef(rightMoveAngle, 1, 0, 0);
	}
	glutSolidCube(0.5);
	glTranslatef(0, -0.5, 0);
	glutSolidCube(0.5);
	lowerRightArm();
	glPopMatrix();
}

void arms(){
	glPushMatrix();
	leftArm();
	rightArm();
	glPopMatrix();
}

void lowerLeftLeg(){
	glTranslatef(0, -0.6, 0);
	glPushMatrix();
    lowerLeftLimbRotate();
	glutSolidCube(0.5);
	glTranslatef(0, -0.5, 0);
	glutSolidCube(0.5);
	glPopMatrix();
}

void lowerRightLeg(){
	glTranslatef(0, -0.6, 0);
	glPushMatrix();
    lowerRightLimbRotate();
	glutSolidCube(0.5);
	glTranslatef(0, -0.5, 0);
	glutSolidCube(0.5);
	glPopMatrix();
}

void leftLeg(){ // green leg
	glColor3b(23, 54, 12);
	glTranslatef(-1.2, 0, 0);
	glPushMatrix();
	if (is_moving || left_leg_moving){
		glRotatef(leftMoveAngle, 1, 0, 0);
	}
	glutSolidCube(0.5);
	glTranslatef(0, -0.5, 0);
	glutSolidCube(0.5);
	lowerLeftLeg();
	glPopMatrix();
}

void rightLeg(){ // blue leg
	glColor3b(23, 54, 87);
	glTranslatef(1.5, 0, 0);
	glPushMatrix();
	if (is_moving || right_leg_moving){
		glRotatef(rightMoveAngle, 1, 0, 0);
	}
	glutSolidCube(0.5);
	glTranslatef(0, -0.5, 0);
	glutSolidCube(0.5);
	lowerRightLeg();
	glPopMatrix();
}

void legs(){
	glTranslatef(0, -2, 0);
	glPushMatrix();
	leftLeg();
	rightLeg();
	glPopMatrix();
}

void drawCreature(){
	head();
	arms();
	legs();
    torso();
}

void resetMoveBooleans(){
	left_move_angle_increasing = true;
	right_move_angle_increasing = false;
	left_leg_moving = false;
	right_leg_moving = false;
	right_arm_moving = false;
	left_arm_moving = false;
	lower_right_leg_moving = false;
	lower_right_arm_moving = false;
	lower_left_leg_moving = false;
	lower_left_arm_moving = false;
	leftMoveAngle = 0;
	rightMoveAngle = 0;
}

void move(){
	resetMoveBooleans();
	if (is_moving){
		is_moving = false;
	} else {
		is_moving = true;
	}
}


// Do spin
void spin() {
	if (is_spinning) {
		is_spinning = false;
		spinAngle = 0.0;
	} else {
		is_spinning = true;
	}
}

void cb_display() {
	glClear(GL_COLOR_BUFFER_BIT);
    
	glLoadIdentity();
    
	camera();
    
	// Rotate along y-axis
	if (is_spinning) {
		glRotatef(spinAngle, 0, 1, 0);
		spinAngle++;
	}
    
	draw_axis(4.0);
    
	glColor3f(1, 1, 1);
	//glutWireTeapot(0.1);
	//glutSolidCube(1.0);
	for (int i = 0; i < duplicates; i++){
		glTranslatef(i*4, 0, 0);
		glPushMatrix();
		drawCreature();
		glPopMatrix();
	}
	glFlush();
	glutSwapBuffers(); // for smoother animation
}

void cb_idle() {
	static clock_t previous_clock = 0;
	static clock_t ms_since_last = 0;
	clock_t now = clock() / (CLOCKS_PER_SEC / 1000);
	ms_since_last = now - previous_clock;
	if (ms_since_last < 10) {
		return;
	}
	if (left_leg_moving || left_arm_moving || is_moving || lower_left_leg_moving || lower_left_arm_moving){
		updateLeftMoveAngle();
	}
	if (right_leg_moving || right_arm_moving || is_moving || lower_right_leg_moving || lower_right_arm_moving){
		updateRightMoveAngle();
	}
	previous_clock = now;
	glutPostRedisplay();
}

void cb_keyboard(unsigned char key, int x, int y) {
	// Add controls to animation, joint movement control, etc.
	// Some camera functions are provided for model viewing convinience.
	switch(key) {
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
		case 'z':
			left_leg_moving ? left_leg_moving = false : left_leg_moving = true;
			break;
		case 'x':
			right_leg_moving ? right_leg_moving = false : right_leg_moving = true;
			break;
		case 'c':
			left_arm_moving ? left_arm_moving = false : left_arm_moving = true;
			break;
		case 'v':
			right_arm_moving ? right_arm_moving = false : right_arm_moving = true;;
			break;
		case 'b':
			lower_left_leg_moving ? lower_left_leg_moving = false : lower_left_leg_moving = true;
			break;
		case 'n':
			lower_right_leg_moving ? lower_right_leg_moving = false : lower_right_leg_moving = true;
			break;
		case '.':
			lower_left_arm_moving ? lower_left_arm_moving = false : lower_left_arm_moving = true;
			break;
		case ',':
			lower_right_arm_moving ? lower_right_arm_moving = false : lower_right_arm_moving = true;
			break;
		case 's':
			spin();
			break;
		case 'm':
			move();
			break;
		case '=':
			duplicates++;
			break;
		case '-':
			duplicates < 1 ? duplicates = 0 : duplicates--;
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
    
	// Help Message:
    
	printf("Instructions:\n\n");
    
	printf("1 is Camera Angle 1.\n");
	printf("2 is Camera Angle 2.\n");
	printf("3 is Camera Angle 3.\n");
	printf("4 is Camera Angle 4.\n");
	printf("5 is Camera Angle 5.\n");
	printf("m is Move.\n");
	printf("z is move the left leg.\n");
	printf("x is move the right leg.\n");
	printf("c is move the left arm.\n");
	printf("v is move the right arm.\n");
	printf("b is move the lower left leg.\n");
	printf("n is move the lower right leg.\n");
	printf(". is move the lower left arm.\n");
	printf(", is move the lower right arm.\n");
	printf("s is spin.\n");
	printf("+ is add an animal.\n");
	printf("- is remove an animal.\n");
	printf("q is Quit.\n");
    
	glutMainLoop();
    
	return 0;
}