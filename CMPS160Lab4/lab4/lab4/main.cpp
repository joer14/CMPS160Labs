//
//// Lab4.cpp : Terrain Mapping
//// Joe Rowley CMPS160 Fall 2013
//// jrowley@ucsc.edu
////
//// this code is UGLY
//
//#include <stdlib.h>
//#include <stdio.h>
//#include <glut/glut.h>
//#include <math.h>
//


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <GLUT/glut.h>
#include <math.h>
#include "util.h"
#include "ppm_canvas.h"
//#include "util.h"

#define PI 3.14159265

float xposition = 0, yposition = 0, zposition = 0;
float xRotation, yRotation = 0, zRotation=0;

int windowWidth, windowHeight;

float spinAngle = 0;
bool is_spinning = false;
bool dListOn= true;
bool textureOn = true;
canvas_t terrain;
canvas_t skin;
GLuint texture;
bool fNorms = true;
float farPlane, nearPlane;

float** fNormals;
float ambientC[3];
float lightX=0;
float lightY=-500;
float lightZ=0;
float lightP[4];
//float lightP[4]={lightX,lightY,lightZ,1.0};

//float lightPosition[4] = {1, 1, 5, 1};
float diffuseColour[3] = {1,.83,.66};
float ambientColour[3] = {0.1,0.1,0.1};
float specularColour[4] = {0, 0, 0, 1};
//
//the functions I used for my lights are

// struct animalSt animalSt;

struct animalSt{
    int x;
    int y;
    int id;
    float animalMoveX =0.0f;
    float animalMoveY =0.0f;
    float animalMoveZ =0.0f;
    float animalForwardAngle =0.0f;
    float animalMoveT =0.0f;
};
typedef struct animalSt animal;
 animalSt an1,an2,an3;
//
//
//struct Y {
//    int r;
//    int s;
//    int t;
//};
//
//struct Y y = { .r = 1, .s = 2, .t = 3 };


//float animalMoveT =0.0f;

//GLuint texture;
GLuint theList;

static int look=0;
// Global variables
float angle = 0;
float armA = 0;
float armA2 = 0;
float spinA = 0;
float teaA = 0;
float bodyTwerk = 1;
static int dup = 1;
static int knee1=0, knee2=0, ank1=0, ank2=0;
//bool is_spinning = false;
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
//didnt end up using this


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

void eye2(){
    //face
    glPushMatrix();
//    glColor3ub(160, 220, 250);
//    glTranslatef(1.5,0.25,-2);
    glutSolidSphere(.25,5,5);
//    glTranslatef(0,-0.5,0);
//    glColor3ub(160, 220, 250);
//    glutSolidSphere(.25,5,5);
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
    glNormal3d(0,1,0);
    
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
    glNormal3d(0,1,0);
    
    glutWireCone(1,3,4,5);
    
    glPopMatrix();
    face();
    
    
    
    glPopMatrix();
}


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

    glNormal3d(0,1,0);
    
    glutWireCube (1.0);
    glPopMatrix();
    
    glTranslatef (1.0, 0.0, 0.0);
    glRotatef ((GLfloat) armA, 0, 1.0, 0);
    
    glTranslatef (2, 0.0, 0.0);
    glPushMatrix();
    glScalef (5.0, 0.4, 1.0);

    glNormal3d(0,1,0);
    
    glutWireCube (1.0);
    glPopMatrix();
    glPushMatrix();
    glPopMatrix();
    glTranslatef(2,0,0);
    glRotatef ((GLfloat) -teaA, 0.0, 0.0, 1.0);
    glNormal3d(0,1,0);
    
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


    glNormal3d(0,1,0);
    
    glutWireCube (1.0);
    glPopMatrix();
    
    glTranslatef (1.0, 0.0, 0.0);
    glRotatef ((GLfloat) armA, 0, 1.0, 0); //swing
    glTranslatef (2, 0.0, 0.0);
    glPushMatrix();
    glScalef (5.0, 0.4, 1.0);
    glNormal3d(0,1,0);
    
    glutWireCube (1.0);
    glPopMatrix();
    
    glTranslatef (2.0, 0.0, 0.0);
    glRotatef(-armA2/2,0,0,1);
    glRotatef ((GLfloat) armA, 0, 1.0, 0); //swing
    glTranslatef (2, 0.0, 0.0);
    glPushMatrix();
    glScalef (5.0, 0.4, 1.0);
    glNormal3d(0,1,0);
    
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

    glNormal3d(0,1,0);
    
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

    glNormal3d(0,1,0);
    
    glutSolidCube (1.0);
    glPopMatrix();
    
    glTranslatef (1.0, 0, 0.0);
    glRotatef(90,0,0,1);
    glRotatef ((GLfloat) ank1, 0.0, 0.0, 1.0);
    glTranslatef (0.5, 0.25, 0.0);
    glPushMatrix();
    glScalef (1.0, 0.4, .75);
    glColor3ub(191, 191, 183);
    glNormal3d(0,1,0);
    
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
    
    glNormal3d(0,1,0);
    
    glutSolidCube (1.0);
    glPopMatrix();
    
    glTranslatef (1.0, 0, 0.0);
    glRotatef(90,0,0,1);
    glRotatef ((GLfloat) ank2, 0.0, 0.0, 1.0);
    
    glTranslatef (0.5, 0.25, 0.0);
    glPushMatrix();
    glScalef (1.0, 0.4, .75);
    glColor3ub(191, 191, 183);

    glNormal3d(0,1,0);
               
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
    glScalef(2.0f,2.0f,2.0f);
    glTranslatef(0,2.5f,0);
//    glTranslatef(terrain.width/2,2.5f,terrain.height/2);
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
void drawTexture() {
 int x, z;
 
 glEnable(GL_TEXTURE_2D);
 glBindTexture(GL_TEXTURE_2D, texture);
   
 glBegin(GL_QUADS);
   glTexCoord2f(0.0f,0.0f);
   glNormal3f(0,0.0,1.0);
   glVertex3f(-10,-10,0);
   
   glTexCoord2f(0.0f,1.0f);
   glVertex3f(-10,10,0);
   
   glTexCoord2f(1.0f,1.0f);
   glVertex3f(10,10,0);
   
   glTexCoord2f(1.0f,0.0f);
   glVertex3f(10,-10,0);
 glEnd();
 glLightfv(GL_LIGHT0, GL_POSITION, lightP);
   
 glDisable(GL_TEXTURE_2D);
}


void diff(float *cResult, float a[3], float b[3]){
   cResult[0] = a[0]-b[0];
   cResult[1] = a[1]-b[1];
   cResult[2] = a[2]-b[2];
}
void normalize(float *nResult, float v[3]){
   float m = sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
 nResult[0]= v[0]/m;
   nResult[1]= v[1]/m;
   nResult[2]= v[2]/m;
}
void cross(float *cResult, float a[3], float b[3]){
   cResult[0] = (a[1]*b[2]) - (a[2]*b[1]);
   cResult[1] = (a[2]*b[0]) - (a[0]*b[2]);
   cResult[2] = (a[0]*b[1]) - (a[1]*b[0]);
   //    printf("vvv: %f, %f, %f,\n",cResult[0], cResult[1], cResult[2]);
};
void sum(float *cResult, float a[3], float b[3]){
   cResult[0] = a[0]+b[0];
   cResult[1] = a[1]+b[1];
   cResult[2] = a[2]+b[2];
}

void compute_normal(float *result, int x, int z, bool upper) {
   //bad boundry cases, should be cleaned up
   if (x-5 == terrain.width) return;
   if (z-5 == terrain.height) return;
   if (x+5 > terrain.width) return;
   if (z+5 > terrain.height) return;
   float e1[3] = {1.0f,float(RED(PIXEL(terrain, x, z+1)))-float(RED(PIXEL(terrain, x, z))),0.0f};
   float e2[3] = {0.0f,float(RED(PIXEL(terrain, x+1, z)))-float(RED(PIXEL(terrain, x, z))),1.0f};
   float e3[3] = {-1.0f,float(RED(PIXEL(terrain, x+1, z)))-   float(RED(PIXEL(terrain, x, z+1))),1.0f};
   float e4[3] = {0.0f,float(RED(PIXEL(terrain, x+1, z+1)))- float(RED(PIXEL(terrain, x, z+1))), 1.0f};
   if(upper){
       result[0] = e1[1]*e2[2]-e1[2]*e2[1];
       result[1] = e1[2]*e2[0]-e1[0]*e2[2];
       result[2] = e1[0]*e2[1]-e1[1]*e2[0];
       return;
   }else{
       result[0] = e3[1]*e4[2]-e3[2]*e4[1];
       result[1] = e3[2]*e4[0]-e3[0]*e4[2];
       result[2] = e3[0]*e4[1]-e3[1]*e4[0];
       result[0] = -result[0];
       result[1] = -result[1];
       result[2] = -result[2];
       
       return;
   }
   
}
void spin() {
 if (is_spinning) {
     is_spinning = false;
     spinAngle = 0.0;
 } else {
     is_spinning = true;
 }
}

void genNormals(){
   float the_normal[3];//
   
   //    fNormals = new float*[terrain.height][terrain.width][2];
   for(int i = 0; i < terrain.height; i++)
   {
       fNormals[i] = new float[terrain.width];
   }
   
   float upper[terrain.height][terrain.width];
   
   
   //    int n,m;
   //    for (n=0;n<terrain.height-1;n++)
   //        for (m=0;m<terrain.width-1;m++)
   //        {
   //            jimmy[n][m][0]=
   //
   //        }
   //
   //
   //    for(int z = 0; z < terrain.height-1; z++){
   //        for(int x = 0; x < terrain.width-1; x++){
   //            compute_normal(the_normal, x, z, true);
   //            upper[x][z][1]=the_normal;
   //            compute_normal(the_normal, x, z, false);
   //            jimmy[x][z][0]=the_normal;
   //            }
   //    }
   
}

void compute_Vnormal(float *result, int x, int z, bool upper) {
   //bad boundry cases, should be cleaned up
   if (x-5 == terrain.width) return;
   if (z-5 == terrain.height) return;
   if (x+5 > terrain.width) return;
   if (z+5 > terrain.height) return;
   //    return result;
   //    x,z+1   TRUE
   //    x+1,z+1 TRUE
   //    x+1,x   TRUE
   //    x,z+1   FALSE
   //    x+1,z+1 FALSE
   //    x+1,x   FALSE
   float n1[3];
   float n2[3];
   float n3[3];
   float n4[3];
   float n5[3];
   float n6[3];
   
   //    compute_normal(n1, x, z+1, true);
   //    compute_normal(n2, x+1, z+1, true);
   //    compute_normal(n3, x+1, z, true);
   //    compute_normal(n4, x, z+1, false);
   //    compute_normal(n5, x+1, z+1, false);
   //    compute_normal(n6, x+1, z, false);
   
   //    compute_normal(n1, x, z+1, true);
   //    compute_normal(n2, x+1, z+1, true);
   //    compute_normal(n3, x+1, z, true);
   //    compute_normal(n4, x, z-1, true);
   //    compute_normal(n5, x-1, z-1, true);
   //    compute_normal(n6, x-1, z, true);
   
   //    -x,z    TRUE
   //    -x, -z  TRUE
   //    x,z-1   treu
   //    x,z+1
   //    x+1,z+1
   //    x+1,x
   
   compute_normal(n1, x, z, true);
   compute_normal(n2, x+1, z, true);
   compute_normal(n3, x, z+1, true);
   compute_normal(n4, x+1, z+1, false);
   compute_normal(n5, x+1, z, false);
   compute_normal(n6, x, z+1, false);
   if (upper){
       
       compute_normal(n1, x, z, true);
       compute_normal(n2, x+1, z, true);
       compute_normal(n3, x, z+1, true);
       compute_normal(n4, x+1, z+1, false);
       compute_normal(n5, x+1, z, false);
       compute_normal(n6, x, z+1, false);
       //    compute_normal(n1, x-1, z, true);
       //    compute_normal(n2, x-1, z-1, true);
       //    compute_normal(n3, x, z-1, true);
       //    compute_normal(n4, x, z+1, false);
       //    compute_normal(n5, x+1, z+1, false);
       //    compute_normal(n6, x+1, z, false);
   }
   else{
       
   }
   result[0]=(n1[0]+n2[0]+n3[0]+n4[0]+n5[0]+n6[0])/ 6.0;
   result[1]=(n1[1]+n2[1]+n3[1]+n4[1]+n5[1]+n6[1])/ 6.0;
   result[2]=(n1[2]+n2[2]+n3[2]+n4[2]+n5[2]+n6[2])/ 6.0;
   
   
   
}
void drawTerrain(){
    
//    eye2();
    
   lightP[0] = lightX;
   lightP[1] = lightY;
   lightP[2] = lightZ;
   
   if(textureOn){
       glEnable(GL_TEXTURE_2D);
       glBindTexture(GL_TEXTURE_2D, texture);
   };
   //    //for maping the texture on
   //    glTranslatef(-(float)(terrain.width - 1) / 2, 0, -(float)(terrain.height -1) / 2);
   
   float the_normal[3];//
   
   
   glEnable(GL_NORMALIZE);
   glBegin(GL_TRIANGLES);
   GLfloat amDiffuse[] = {0.f, .8f, .8f, 0.f};
   glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, amDiffuse);
   
   for(int z = 0; z < terrain.height-1; z++){
       for(int x = 0; x < terrain.width-1; x++){
           if(fNorms){
               //upper
               compute_normal(the_normal, x, z, true);
               glNormal3f(the_normal[0], the_normal[1], the_normal[2]);
               
               //x, y, z
               glTexCoord2f((float)(x) / terrain.width, (float)(z) / terrain.height);
               
               glVertex3f(x, float(RED(PIXEL(terrain, x, z))), z);
               //x,y,z+1
               glTexCoord2f((float)(x) / terrain.width, (float)(z+1) / terrain.height);
               glVertex3f(x,float(RED(PIXEL(terrain, x, z+1))), z+1 );
               //x+1,y,z
               glTexCoord2f((float)(x+1) / terrain.width, (float)(z) / terrain.height);
               glVertex3f(x+1, float(RED(PIXEL(terrain, x+1, z))),z );
               
               
               //lower
               
               compute_normal(the_normal, x, z, false);
               glNormal3f(the_normal[0], the_normal[1], the_normal[2]);
               //x,y,z+1
               glTexCoord2f((float)(x) / terrain.width, (float)(z+1) / terrain.height);
               glVertex3f(x, float(RED(PIXEL(terrain, x, z+1))), z+1);
               //x+1,y,z
               glTexCoord2f((float)(x+1) / terrain.width, (float)(z) / terrain.height);
               glVertex3f(x+1, float(RED(PIXEL(terrain, x+1, z))), z);
               //x+1, y+1, z+1
               glTexCoord2f((float)(x+1) / terrain.width, (float)(z+1) / terrain.height);
               glVertex3f(x+1, float(RED(PIXEL(terrain, x+1, z+1))), z+1);
           }
           else{
               //caluate using fNormals
               //upper
               
               //x, y, z
               compute_Vnormal(the_normal, x, z, true);
               glNormal3f(the_normal[0], the_normal[1], the_normal[2]);
               glTexCoord2f((float)(x) / terrain.width, (float)(z) / terrain.height);
               glVertex3f(x, float(RED(PIXEL(terrain, x, z))), z);
               
               //x,y,z+1
               compute_Vnormal(the_normal, x, z+1, true);
               glNormal3f(the_normal[0], the_normal[1], the_normal[2]);
               glTexCoord2f((float)(x) / terrain.width, (float)(z+1) / terrain.height);
               glVertex3f(x,float(RED(PIXEL(terrain, x, z+1))), z+1 );
               
               //x+1,y,z
               compute_Vnormal(the_normal, x+1, z, true);
               glNormal3f(the_normal[0], the_normal[1], the_normal[2]);
               glTexCoord2f((float)(x+1) / terrain.width, (float)(z) / terrain.height);
               glVertex3f(x+1, float(RED(PIXEL(terrain, x+1, z))),z );
               
               //x,y,z+1
               compute_Vnormal(the_normal, x, z+1, false);
               glNormal3f(the_normal[0], the_normal[1], the_normal[2]);
               glTexCoord2f((float)(x) / terrain.width, (float)(z+1) / terrain.height);
               glVertex3f(x, float(RED(PIXEL(terrain, x, z+1))), z+1);
               
               //x+1,y,z
               compute_Vnormal(the_normal, x+1, z, false);
               glNormal3f(the_normal[0], the_normal[1], the_normal[2]);
               glTexCoord2f((float)(x+1) / terrain.width, (float)(z) / terrain.height);
               glVertex3f(x+1, float(RED(PIXEL(terrain, x+1, z))), z);
               
               //x+1, y+1, z+1
               compute_Vnormal(the_normal, x+1, z+1, false);
               glNormal3f(the_normal[0], the_normal[1], the_normal[2]);
               glTexCoord2f((float)(x+1) / terrain.width, (float)(z+1) / terrain.height);
               glVertex3f(x+1, float(RED(PIXEL(terrain, x+1, z+1))), z+1);
               
               
               
           }
       }
   }
    
    glPushMatrix();
//    glScalef(0.1f,0.1f,0.1f);
//    animalTime();
   
    glPopMatrix();
   glEnd();
   if(textureOn){glDisable(GL_TEXTURE_2D);}
   //    printf("Created Triangle Strip\n");
    
   
}



void rotateCamera(void){
   glRotatef(xRotation, 1, 0, 0);
   glRotatef(yRotation, 0, 1, 0);
   glTranslatef(-xposition, -yposition, -zposition);
   
   // Rotate along y-axis
 if (is_spinning) {
     glRotatef(spinAngle, 0, 1, 0);
     spinAngle = spinAngle+1;
 }
}
void newDList(){
   theList = glGenLists(1);
   glNewList(theList, GL_COMPILE);
   //drawing functions below
   drawTerrain();
   glEndList();
}

// void cb_display() {
    
    
    
    
    
    
    
    
//     glFlush();
//     glutSwapBuffers(); // for smoother animation
// }
//void updateAnimalMove(float *animalMoveX,float *animalMoveY, float *animalMoveZ){
//    
//}
//
//void update2(struct animal);

void update2(animal *an){
//    t = t+.01;
    int x= (an->x);
    int y= an->y;
    if(an->animalMoveT>360) an->animalMoveT=0;
    
    
    if (an->id == 1){
        an->animalMoveT += 0.01f;
//        an->animalMoveT= animalMoveT;
        
        float dx = an->animalMoveX - (x +cos(an->animalMoveT)*50);
        float dz = an->animalMoveZ - (y +sin(an->animalMoveT)*50);
        an->animalMoveX = x +cos(an->animalMoveT)*50;
        an->animalMoveZ = y +sin(an->animalMoveT)*50;
        //height map
        //call bilinear inter here
        an->animalMoveY = float(RED(PIXEL(terrain, (int)an->animalMoveX, (int)an->animalMoveZ)));
        an->animalForwardAngle = atan2 (dx,dz) * 180 / PI;;
        an->animalForwardAngle += 90.0f;
    }
    if (an->id == 2){
        an->animalMoveT += 0.01f;
//        an->animalMoveT= animalMoveT;
        
        float dx = an->animalMoveX - (x +sin(an->animalMoveT)*50);
        float dz = an->animalMoveZ - (y +cos(an->animalMoveT)*50);
        an->animalMoveX = x +sin(an->animalMoveT)*50;
        an->animalMoveZ = y +cos(an->animalMoveT)*50;
        //height map
        //call bilinear inter here
        an->animalMoveY = float(RED(PIXEL(terrain, (int)an->animalMoveX, (int)an->animalMoveZ)));
        an->animalForwardAngle = atan2 (dx,dz) * 180 / PI;;
        an->animalForwardAngle += 90.0f;
    }
    if (an->id == 3){
        an->animalMoveT += 0.02f;
//        an->animalMoveT= animalMoveT;
        
        float dx = an->animalMoveX - (x +sin(an->animalMoveT)*30);
        float dz = an->animalMoveZ - (y +cos(an->animalMoveT)*50);
        an->animalMoveX = x + sin(an->animalMoveT)*30;
        an->animalMoveZ = y + cos(an->animalMoveT)*50;
        //height map
        //call bilinear inter here
        an->animalMoveY = float(RED(PIXEL(terrain, (int)an->animalMoveX, (int)an->animalMoveZ)));
        an->animalForwardAngle = atan2 (dx,dz) * 180 / PI;;
        an->animalForwardAngle += 90.0f;
    }
//    printf("forward ang: %f \n",an.animalForwardAngle);
    printf("time: %f\n",an->animalMoveT);
//    printf("X: %f\n",an->animalMoveX);
//    prinft(")
}
void animalMove(){
//    if(animalMoveT>360) animalMoveT=0;
//    animalMoveT += 0.01f;

    an1.id = 1;
    an2.id = 2;
    an3.id = 3;
    an1.x = an1.y = 128;
    an2.x = 64;
    an2.y = 128;
    an3.x = 128;
    an3.y = 64;
    
    
    update2(&an1);
    update2(&an2);
    update2(&an3);
    glPushMatrix();
    glTranslatef(an1.animalMoveX,an1.animalMoveY,an1.animalMoveZ);
    glRotatef(an1.animalForwardAngle,0.0f,1.0f,0.0f);
    animalTime();
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(an2.animalMoveX,an2.animalMoveY,an2.animalMoveZ);
    glRotatef(an2.animalForwardAngle,0.0f,1.0f,0.0f);
    animalTime();
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(an3.animalMoveX,an3.animalMoveY,an3.animalMoveZ);
    glRotatef(an3.animalForwardAngle,0.0f,1.0f,0.0f);
    animalTime();
    glPopMatrix();

    //    printf("An1 X: %f\n",an1.animalMoveX);

}

void cb_display() {
 glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
 glLoadIdentity();
   
   
   rotateCamera();
   
   //
   //let there be light!
   //
   glEnable(GL_DEPTH_TEST);
   glEnable(GL_LIGHTING);
   glEnable(GL_LIGHT0);
   //    glDisable(GL_LIGHTING);
   glEnable(GL_COLOR_MATERIAL);
   glShadeModel(GL_SMOOTH);
   
   
   
   
   glPushMatrix();
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluPerspective(90, windowWidth/windowHeight, nearPlane, farPlane);
   glMatrixMode(GL_MODELVIEW);
   glPopMatrix();
   
    if(look == 0){
    gluLookAt(-50,100,-50,
             0,0,0,
             0,1,0);
    }
    if(look == 1){
        gluLookAt(an1.animalMoveX - 20,an1.animalMoveY + 50 ,an1.animalMoveZ - 20,
                  an1.animalMoveX,an1.animalMoveY,an1.animalMoveZ,
                  0,1,0);
    }
    if(look == 2){
        gluLookAt(an2.animalMoveX - 20,an2.animalMoveY + 50 ,an2.animalMoveZ - 20,
                  an2.animalMoveX,an2.animalMoveY,an2.animalMoveZ,
                  0,1,0);
    }
    if(look == 3){
        gluLookAt(an3.animalMoveX - 20,an3.animalMoveY + 50 ,an3.animalMoveZ - 20,
                  an3.animalMoveX,an3.animalMoveY,an3.animalMoveZ,
                  0,1,0);
    }
    if(look == 4){
        gluLookAt(10,300,10,
                  128,0,128,
                  0,1,0);
    }
   glPushMatrix();
   
   //if we should use the displaylist then use that,
   // otherwise render the regular way
   
   if(dListOn){
       glCallList(theList);
   }
   else{
       drawTerrain();
   }
   
    
    //start
    
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
    
    //    camera();
    
    // Rotate along y-axis
    if (is_spinning) {
        glRotatef(angle, 0, 1, 0);
        angle++;
    }
    
//    draw_axis(4.0);
    
//    glColor3f(1, 1, 1);
//    animalTime();
//    glPushMatrix();
    
//    glTranslatef(-0.0f,-0.2f,-0.2f);
//    glScalef(0.1f,0.1f,0.1f);
//    glTranslatef(i*6,0,i*6);
//    glPopMatrix();
    
//    for (int i=0; i<dup; i++){
//        glPushMatrix();
//        glTranslatef(i*6,0,i*6);
//        animalTime();
//        glPopMatrix();
//    }
    
    
    //end
   
   glLightfv(GL_LIGHT0, GL_POSITION, lightP);
   glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseColour);
   glLightfv(GL_LIGHT0, GL_AMBIENT, ambientColour);
   glLightfv(GL_LIGHT0, GL_SPECULAR, specularColour);
   
   
  

    
   glPopMatrix();
   
   draw_axis(4.0);
    if (animate){
    animalMove();
    }
    drawTerrain();//
//    drawTexture();
    
    
 glFlush();
 glutSwapBuffers(); // for smoother animation
   
   
   
   
}
void loadTextureMap(canvas_t tex) {
    glEnable(GL_TEXTURE_2D);
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
//    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, tex.width, tex.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, tex.pixels);
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glDisable(GL_TEXTURE_2D);
}

void cb_idle() {
    //	drawTexture();
    //    drawTerrain();
	glutPostRedisplay();
}

void cb_reshape(int w, int h) {
    windowWidth = w;
    windowHeight = h;
    int aspectRatio = w/h;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(90.0, aspectRatio, nearPlane, farPlane);
    glMatrixMode(GL_MODELVIEW);
}

// void cb_reshape(int w, int h) {
//     glViewport(0, 0, w, h);
//     glMatrixMode(GL_PROJECTION);
//     glLoadIdentity();
//     glFrustum(-1.0, 1.0, -1.0, 1.0, 1.0, 100.0);
//     glMatrixMode(GL_MODELVIEW);
// }

void cb_keyboard(unsigned char key, int x, int y) {
    // Add controls to animation, joint movement control, etc.
    // Some camera functions are provided for model viewing convinience.
    // switch(key) {
    //     case'W':
    //         wireframe = !wireframe;
    //         break;
    //     case'a':
    //         animate= !animate;
    //         break;
    //     // case 'd':
    //     //     duplicate(0);
    //     //     break;
    //     // case 'D':
    //     //     duplicate(1);
    //     //     break;
    //     case 'q':
    //         exit(0);
    //         break;

        //    switch(key) {
//    printf("keyboard callback \n");
    if (key == '1') look = 1;
    if (key == '0') look = 0;
    if (key == '2') look = 2;
    if (key == '3') look = 3;
    if (key == '4') look = 4;
   if (key == 'b'){
       dListOn = !dListOn;
   }
   if(key == 'c')
   {
       xRotation += 1;
       if(xRotation > 360) xRotation -= 360;
   }
   
   if(key == 'v')
   {
       xRotation -= 1;
       if(xRotation < -360) xRotation -= 360;
   }
   if(key == 'w')
   {
       float xRotationrad, yRotationrad;
       xRotationrad = (xRotation / 180 * PI);
       yRotationrad = (yRotation / 180 * PI);
       xposition += float(sin(yRotationrad));
       yposition -= float(sin(xRotationrad));
       zposition -= float(cos(yRotationrad));
   }
   
   if(key == 's')
   {
       float xRotationrad, yRotationrad;
       xRotationrad = (xRotation / 180 * PI);
       yRotationrad = (yRotation / 180 * PI);
       xposition -= float(sin(yRotationrad));
       yposition += float(sin(xRotationrad));
       zposition += float(cos(yRotationrad));
       //        printf("x: %f, y: %f, z: %f \n",xposition,yposition,zposition);
   }
   
   if(key == 'd')
   {
       float yRotationrad;
       yRotationrad = (yRotation / 180 * PI);
       xposition += float(cos(yRotationrad));
       zposition += float(sin(yRotationrad));
   }
   
   if(key == 'a')
   {
       float yRotationrad;
       yRotationrad = (yRotation / 180 * PI);
       xposition -= float(cos(yRotationrad));
       zposition -= float(sin(yRotationrad));
   }
   if (key =='S') spin();
   
   if( key =='i'){
       lightX += 50;
       //        printf("Moved Light Down\n");
       //        printf("lightX: %f, lightY:%f, LightZ:%f \n",lightX,lightY,lightZ);
       
   }
   if( key =='k'){
       lightX -= 50;
       
       //cc        printf("Moved Light Up \n");
   }
   if( key =='j'){
       lightZ += 50;
       
       //        printf("Moved Light Right\n");
   }
   if( key =='l'){
       lightZ -= 50;
       //        printf("Moved Light Left\n");
   }
   if (key =='t'){
       textureOn = !textureOn;
   }
   if (key =='q'){
        exit(0);
   }
   if (key =='A'){
       animate= !animate;
   }
}



int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 800);
    glutCreateWindow("Lab 2: Robotic Animals");
//check this
//    glutIgnoreKeyRepeat(true);

    glEnable(GL_COLOR_MATERIAL);
    
	if (argc == 3) {
        
        printf("Loading file '%s'... ", argv[1]);
        ppmLoadCanvas(argv[1], &terrain);
        printf("Done.\n");
        printf("Loading file '%s'... ", argv[2]);
        ppmLoadCanvas(argv[2], &skin);
        loadTextureMap(skin);
        printf("Done.\n");
        
        
	} else {
		printf("Usage: %s terrain.ppm texture.ppm\n", argv[0]);
		return 1;
	}
    printf("Welcome!!!\n"
           "Controls:\n\n"
           "c/v to rotate up/down \n"
           "WASD to move around the terrain\n"
           "n/N to decrease/increase near plane distance\n"
           "m/M to decrease/increase far plane distance\n"
           "i/k to move the light up/down\n"
           "j/l to move the light left/right\n"
           "S to spin\n"
           "f switch from Face normals to vertex normals\n"
           "b switch on/off display mode(on by default)\n"
           "t switch textures on/off\n"
           "q to quit\n"
           );
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glEnable (GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
    
    nearPlane = .1;
    farPlane = 1000;
    //
    glDepthFunc(GL_LEQUAL);
    
    newDList();
    
    
	
    
	
	
    glutDisplayFunc(cb_display);
    glutReshapeFunc(cb_reshape);
    glutIdleFunc(cb_idle);
    glutKeyboardFunc(cb_keyboard);
    
    glClearColor(255,0,0,0); // set background to black
    printf("Welcome! Here are the controls. \n A on/off Animation \n S on/off spining \n Q to Quit \n \n G g Move Right Leg \n H h Move Left Leg \n J j move Right Foot \n K k Move Left Foot \n U u Change rotation 1st arm segment \n I i Change rotation 2nd arm segment \n O o Pour Tea");
    glutMainLoop();
    
   
	return 0;
}

//int main(int argc, char** argv) {
//
//	
//}


//

////cache

//
//

//

//void cb_mouseclick(int button, int state, int x, int y) {
//}
//
//void cb_mousemove(int x, int y) {
//}
//
//void callback_keyboard(unsigned char key, int x, int y) {



//    //    cb_reshap
//}
//
//

