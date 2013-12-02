/**
* CMPS 160L (Fall 2013)
* Lab 2: Animated Animal
* Joe Rowley jrowley@ucsc.edu 
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <GLUT/glut.h>
#include <math.h>
#include "util.h"
// Global variables
float angle = 0;
float armA = 0;
float armA2 = 0;
float spinA = 0;
float teaA = 0;
float bodyTwerk = 1;
static int dup = 1;
static int knee1=0, knee2=0, ank1=0, ank2=0;
bool is_spinning = false;
bool wireframe = false;
bool rKnee1 = true;
bool rAnk1 = true;
bool rAnk2 = false;
bool animate = false;
bool armABack = true;
bool moveArm = true;
bool moveTea = false;
static int rt=255, bt=0, gt=200;
// Do spin
void spin() {
        if (is_spinning) {
                is_spinning = false;
                angle = 0.0;
        } else {
                is_spinning = true;
        }
}
//didnt end up using this
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
void eye(){
    //face
    glPushMatrix();
    glColor3ub(160, 220, 250);
    glTranslatef(1.5,0.25,-2);
    glutSolidSphere(.25,5,5);
    glTranslatef(0,-0.5,0);
    glColor3ub(160, 220, 250);
    glutSolidSphere(.25,5,5);
    glPopMatrix();
    
}
void mouth(){
    glColor3ub(245, 29, 201);
    glPushMatrix();
    glTranslatef(1.5,0,0);

//    glScalef(.2,.2,.2);
    
    glBegin(GL_TRIANGLE_STRIP);
    glVertex3f(0,0,0);
    glVertex3f(1,2,0);
    glVertex3f(-1,2,0);
//    //middle section
//    glVertex3f(-1,5,0);
//    glVertex3f(1,5,0);
//    
//    glVertex3f(1,2,0);
//    //top
//    glVertex3f(-1,5,0);
//    glVertex3f(1,5,0);
//    glVertex3f(0,7,-1);
    glEnd();
    glPopMatrix();
}

void face(){
    eye();
//    mouth();
//    glPushMatrix()
}
void body(){
    glColor3ub(245, 239, 37);
    glRotatef(90,1,0,0);
    glRotatef(25,0,1,0);
    glTranslatef(0,0,.25);
    glPushMatrix();
    float t = .35;
    float shear2[] = {
        1, 0, -t, 0,
        0, 1, 0, 0,
       -t, 0, 1, 0,
        0, 0, 0, 1 };
    glMultMatrixf(shear2);
//
    
//    glRotatef(
    float shear[] = {
        1, 0, t, 0,
        0, 1, 0, 0,
        t, 0, 1.3, 0,
        0, 0, 0, 1 };
    glMultMatrixf(shear);
    glutWireCone(1,3,4,5);
    glPopMatrix();
    
    glPushMatrix();
    float shear3[] = {
        1, 0, -t, 0,
        0, 1, 0, 0,
        -t, 0, 1, 0,
        0, 0, 0, 1 };
    glMultMatrixf(shear3);
    //
    
    //    glRotatef(
    float shear4[] = {
        1, 0, t, 0,
        0, 1, 0, 0,
        t, 0, -1, 0,
        0, 0, 0, 1 };
//    glRotatef(90,0,0,1);

    glMultMatrixf(shear4);
    glutWireCone(1,3,4,5);
    
    glPopMatrix();
    face();
    
    
    
    glPopMatrix();
}


//void leg(){
//    glRotatef(-90,0,0,1);
//    glPushMatrix();
//    glTranslatef (-1.0, 0.0, 0.0);
//    glRotatef ((GLfloat) knee1, 0.0, 0.0, 1.0);
//    glTranslatef (1.0, 0.0, 0.0);
//    glPushMatrix();
//    glScalef (2.0, 0.4, 1.0);
//    glColor3ub(20, 191, 183);
//    
//    glutSolidCube (1.0);
//    glPopMatrix();
//    
//    glTranslatef (1.0, 0, 0.0);
//    glRotatef(90,0,0,1);
//    glRotatef ((GLfloat) ank1, 0.0, 0.0, 1.0);
//    glTranslatef (0.5, 0.25, 0.0);
//    glPushMatrix();
//    glScalef (1.0, 0.4, .75);
//    glColor3ub(191, 191, 183);
//    glutSolidCube (1.0);
//    glPopMatrix();
//
//    glPopMatrix();
////    glutSwapBuffers();
//}
void leftArm(){
    glColor3ub(255, 200, 0);
    
    glRotatef(90,0,1,0);
    glScalef(.5,1,.5);
    glPushMatrix();
    glTranslatef (-1.0, 0.0, 0.0);
    glRotatef ((GLfloat) 0, 0.0, 0.0, 1.0);
    glTranslatef (1.0, 0.0, 0.0);
    glPushMatrix();
    glScalef (3.0, 0.4, 1.0);
    glutWireCube (1.0);
    glPopMatrix();
    
    glTranslatef (1.0, 0.0, 0.0);
    glRotatef ((GLfloat) armA, 0, 1.0, 0);
    
    glTranslatef (2, 0.0, 0.0);
    glPushMatrix();
    glScalef (5.0, 0.4, 1.0);
    glutWireCube (1.0);
    glPopMatrix();
    glPushMatrix();
    glPopMatrix();
    glTranslatef(2,0,0);
    glRotatef ((GLfloat) -teaA, 0.0, 0.0, 1.0);
    
    glutWireTeapot(1);
    
    
    glPopMatrix();
    
    
}
void rightArm(){
    glColor3ub(255, 200, 0);
    
    glRotatef(90,0,1,0);
    glScalef(.5,1,.5);
    glPushMatrix();
    glTranslatef (-1.0, 0.0, 0.0);
    glRotatef ((GLfloat) 0, 0.0, 0.0, 1.0);
    glTranslatef (1.0, 0.0, 0.0);
    glPushMatrix();
    glScalef (3.0, 0.4, 1.0);
    glutWireCube (1.0);
    glPopMatrix();
    
    glTranslatef (1.0, 0.0, 0.0);
    glRotatef ((GLfloat) armA, 0, 1.0, 0); //swing
    glTranslatef (2, 0.0, 0.0);
    glPushMatrix();
    glScalef (5.0, 0.4, 1.0);
    glutWireCube (1.0);
    glPopMatrix();
    
    glTranslatef (2.0, 0.0, 0.0);
    glRotatef(-armA2/2,0,0,1);
    glRotatef ((GLfloat) armA, 0, 1.0, 0); //swing
    glTranslatef (2, 0.0, 0.0);
    glPushMatrix();
    glScalef (5.0, 0.4, 1.0);
    glutWireCube (1.0);
    glPopMatrix();
    
    
    glPushMatrix();
    glPopMatrix();
    glTranslatef(2,0,0);
    glRotatef ((GLfloat) -teaA, 0.0, 0.0, 1.0);
//    rt=;
    int teaA2 = (int)teaA;
    rt=(int)(255 - teaA2*(255/90));
    gt=(int)(200 - teaA2*(200/90));
    bt=(int)(teaA2*255/90);
    glColor3ub(rt, gt, bt);
    glutWireTeapot(1);
//    printf("teaA %d, %d, %d, %d\n",(int)teaA,rt,gt,bt);
    
    
    glPopMatrix();
    
    
}


void leftLeg(){
    glPushMatrix();
    glRotatef(15,0,1,0);
    glScalef(-.8,1,1);
//    leg();
    glRotatef(-90,0,0,1);
    glPushMatrix();
    glTranslatef (-1.0, 0.0, 0.0);
    glRotatef ((GLfloat) knee1, 0.0, 0.0, 1.0);
    glTranslatef (1.0, 0.0, 0.0);
    glPushMatrix();
    glScalef (2.0, 0.4, 1.0);
    glColor3ub(20, 191, 183);
    
    glutSolidCube (1.0);
    glPopMatrix();
    
    glTranslatef (1.0, 0, 0.0);
    glRotatef(90,0,0,1);
    glRotatef ((GLfloat) ank1, 0.0, 0.0, 1.0);
    glTranslatef (0.5, 0.25, 0.0);
    glPushMatrix();
    glScalef (1.0, 0.4, .75);
    glColor3ub(191, 191, 183);
    glutSolidCube (1.0);
    glPopMatrix();
    glPopMatrix();
    glPopMatrix();
}
void rightLeg(){
    glPushMatrix();
    glRotatef(15,0,1,0);
    glScalef(-0.8,1,1);
    glRotatef(-90,0,0,1);
    glPushMatrix();
    glTranslatef (-1.0, 0.0, 0.0);
    glRotatef ((GLfloat) knee2, 0.0, 0.0, 1.0);
    glTranslatef (1.0, 0.0, 0.0);
    glPushMatrix();
    glScalef (2.0, 0.4, 1.0);
    glColor3ub(20, 191, 183);
    
    glutSolidCube (1.0);
    glPopMatrix();
    
    glTranslatef (1.0, 0, 0.0);
    glRotatef(90,0,0,1);
    glRotatef ((GLfloat) ank2, 0.0, 0.0, 1.0);
    
    glTranslatef (0.5, 0.25, 0.0);
    glPushMatrix();
    glScalef (1.0, 0.4, .75);
    glColor3ub(191, 191, 183);
    glutSolidCube (1.0);
    glPopMatrix();
    
    glPopMatrix();
    glPopMatrix();
}

void animateKnee(){
    if(rKnee1){
        knee1 = (knee1 + 5) % 360;
            }
    else{
        knee1 = (knee1 - 5) % 360;
    }

    if (knee1 > 80) {
        rKnee1 = false;
        rAnk1= true;
    }
    if (knee1 < -60) {
        rKnee1 = true;
        rAnk1 = false;
    }
    knee2 = (-knee1)% 360;
    
}
void animateAnk(){
    if (rAnk1){
        ank1 = (ank1 + 5) % 360;
    }
    else ank1 = (ank1 - 5) % 360;
    
    if (rAnk2){
        ank2 = (ank2 + 5) % 360;
    }
    else ank2 = (ank2 - 5) % 360;
    
    ank2= (-ank1 - 20)% 360;
//    ank3= (ank2 -90)%360;
    
}

void teaTime(){
    if (teaA >90) {
        moveTea = false;
        moveArm = false;
    }
    
    if (teaA == 0 && !moveTea && !moveArm) {
        moveArm = true;
        
    }
    
    
    if (!moveArm && moveTea){
        teaA = ((int)teaA + 1) % 360;
    }
    if (!moveArm && !moveTea){
        teaA = ((int)teaA - 1) % 360;
    }
    
    }

void animateArm(){
 
//    printf("armA: %d\n", (int)teaA);
    

    if (moveArm) {
        if (!armABack){
            armA = ((int)armA + 1) % 360;
            
            if (armA2 < 45){
            armA2 = ((int)armA2 + 1) % 360;
            }

        }else {
            armA = ((int)armA - 1) % 360;
                armA2 = ((int)armA2 - 1) % 360;
        }
        
        if (armA > 45){
            armABack = true;
            moveArm = false;
            moveTea = true;
            teaTime();
        }
        if (armA < -45){
            armABack = false;
        }
        
    }
    else teaTime();
}

void animalTime(){
    glPushMatrix();
    glPushMatrix();
    glTranslatef(0,.3,-.5);
    glScalef(1,1.5,.5);
    leftLeg();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0,.3,.5);
    glScalef(1,1.5,.5);
    rightLeg();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0,5,0);
    rightArm();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0,5,0);
    glScalef(-1,1,-1);
    rightArm();
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(0,3,0);
    body();
    glPopMatrix();
    glPopMatrix();
}
void duplicate(bool add){
    if (add){
        dup = dup+1;
    }else dup = dup-1;
    printf("dups:%d\n",dup);
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
    
    if (animate){
        animateKnee();
        animateAnk();
        animateArm(); 
    };
//    int armAB = armA % (uintmax_t)now;
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
    
    for (int i=0; i<dup; i++){
        glPushMatrix();
        glTranslatef(i*6,0,i*6);
        animalTime();
        glPopMatrix();
    }
    
    
    
    
    
    
    
    
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
        case'W':
            wireframe = !wireframe;
            break;
        case'a':
            animate= !animate;
            break;
        case'w':
            wiggle();
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
        case 'g':
            knee1 = (knee1 + 5) % 360;
            break;
        case 'G':
            knee1 = (knee1 - 5) % 360;
            break;
        case 'h':
            knee2 = (knee2 + 5) % 360;
            break;
        case 'H':
            knee2 = (knee2 - 5) % 360;
            break;
        case 'J': 
            ank1 = (ank1 + 5) % 360;
            break;
        case 'j':  
            ank1 = (ank1 - 5) % 360;
            break;
        case 'K': 
            ank2 = (ank2 + 5) % 360;
            break;
        case 'k': 
            ank2 = (ank2 - 5) % 360;
            break;
            
        case 'o':
            armA = ((int)armA - 5) % 360;
            break;
        case 'O':
            armA = ((int)armA + 5) % 360;
            break;
        case 'i':
            armA2 = ((int)armA2 - 5) % 360;
            break;
        case 'I':
            armA2 = ((int)armA2 + 5) % 360;
            break;
        case 'p':
            teaA = ((int)teaA - 5) % 360;
            break;
        case 'P':
            teaA = ((int)teaA + 5) % 360;
            break;
    
        case 'd':
            duplicate(0);
            break;
        case 'D':
            duplicate(1);
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
    printf("Welcome! Here are the controls. \n A on/off Animation \n S on/off spining \n Q to Quit \n \n G g Move Right Leg \n H h Move Left Leg \n J j move Right Foot \n K k Move Left Foot \n U u Change rotation 1st arm segment \n I i Change rotation 2nd arm segment \n O o Pour Tea");
        glutMainLoop();

        return 0;
}