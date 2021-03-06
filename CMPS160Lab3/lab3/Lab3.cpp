
// Lab3.cpp : Terrain Mapping
// Joe Rowley CMPS160 Fall 2013
// jrowley@ucsc.edu
// this code is UGLY

#include <stdlib.h>
#include <stdio.h>
#include <glut/glut.h>
#include <math.h>

#include "ppm_canvas.h"
#include "util.h"

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



//GLuint texture;
GLuint theList;

void drawTexture() {
	int x, z;
	
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture);
//	gluLookAt
//    (1,0,0,
//     1,0,0,
//     0,1,0);
    
//	gluLookAt(0,0,15,0,0,0,0,1,0);
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



void loadHeights(){
    
}
//face normal is regular - computes the cross product between 2 given vectors
//
//
//
//   
//
//
//
//
//
//vertex normal is the average of the 6 triangles that touch the given triangle
//void compute

//computers the normal for a given triangle
//
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
    //e1 = v2-v1
    //e2 = v3-v1
    //e3 = v3-v2
    //e4 = v4-v2
    //e5 = v2-v4
    //e6 = v3-v4
    //    float v1[3]= {(float)x,float(RED(PIXEL(terrain, x, z))), (float)z};
    //    float v2[3]= {(float)x,float(RED(PIXEL(terrain, x, z+1))), (float)z+1};
    //    float v3[3]= {(float)x+1,float(RED(PIXEL(terrain, x+1, z))), (float)z};
    //    float v4[3]= {(float)x+1, float(RED(PIXEL(terrain, x+1, z+1))), (float)z+1};
    //
    
    float e1[3] = {1.0f,float(RED(PIXEL(terrain, x, z+1)))-float(RED(PIXEL(terrain, x, z))),0.0f};
    float e2[3] = {0.0f,float(RED(PIXEL(terrain, x+1, z)))-float(RED(PIXEL(terrain, x, z))),1.0f};
//    float e3[3] = {1.0f,float(RED(PIXEL(terrain, x+1, z)))-float(RED(PIXEL(terrain, x, z+1))),1.0f};
//    float e4[3] = {1.0f,float(RED(PIXEL(terrain, x+1, z+1)))- float(RED(PIXEL(terrain, x, z+1))), 0.0f};
    float e3[3] = {-1.0f,float(RED(PIXEL(terrain, x+1, z)))-   float(RED(PIXEL(terrain, x, z+1))),1.0f};
    float e4[3] = {0.0f,float(RED(PIXEL(terrain, x+1, z+1)))- float(RED(PIXEL(terrain, x, z+1))), 1.0f};
//    float e5[3] = {
//    cross.x = e1.y*e2.z - e1.z*e2.y
//    cross.y = e1.z*e2.x - e1.x*e2.z
//    cross.z = e1.x*e2.y - e1.y*e2.x
    
    //    cross.x = e1.1*e2.2 - e1.2*e2.1
    //    cross.y = e1.2*e2.0 - e1.0*e2.2
    //    cross.z = e1.0*e2.1 - e1.1*e2.0
    if(upper){
        result[0] = e1[1]*e2[2]-e1[2]*e2[1];
        result[1] = e1[2]*e2[0]-e1[0]*e2[2];
        result[2] = e1[0]*e2[1]-e1[1]*e2[0];
//        printf("Upper: x: %f y: %f z:%f \n",result[0],result[1],result[2]);
//        normalize(result,result);
//        printf("Upper: x: %f y: %f z:%f \n",result[0],result[1],result[2]);
        return;
    }else{
        result[0] = e3[1]*e4[2]-e3[2]*e4[1];
        result[1] = e3[2]*e4[0]-e3[0]*e4[2];
        result[2] = e3[0]*e4[1]-e3[1]*e4[0];
        result[0] = -result[0];
        result[1] = -result[1];
        result[2] = -result[2];
//        normalize(result,result);
//        printf("Lower: x: %f y: %f z:%f \n",result[0],result[1],result[2]);
        
        return;
    }
    
//////    printf("z: %d x: %d\n",z, x);
////  

//    //float(RED(PIXEL(terrain, x, z)))
//    float e1[3];
//    float e2[3];
//    float r2[3];
//    if (upper){
//        diff(e1,v2,v1);
//        diff(e2,v3,v1);
//        cross(result,e1,e2);
////        normalize(r2, r2);
////         printf("for x: %d, y:%f, z:%d \n",x,float(RED(PIXEL(terrain, x, z))),z);
////         printf("x: %f, y:%f, z:%f \n",r2[0],r2[1],r2[2]);
//    }else{
//        diff(e1,v2,v4);
//        diff(e2,v3,v4);
//        cross(result,e1,e2);
////        normalize(result, r2);
//    }
    
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
//    x,z+1	TRUE
//    x+1,z+1	TRUE
//    x+1,x	TRUE
//    x,z+1	FALSE
//    x+1,z+1	FALSE
//    x+1,x	FALSE
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
    
//    -x,z	TRUE
//    -x, -z 	TRUE
//    x,z-1	treu
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
//cache
void newDList(){
    theList = glGenLists(1);
    glNewList(theList, GL_COMPILE);
    //drawing functions below
        drawTerrain();
    glEndList();
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

    gluLookAt(300,250,300,
              0,0,0,
              0,1,0);
    
    
    
    
    glPushMatrix();
    
    //if we should use the displaylist then use that,
    // otherwise render the regular way
    
    if(dListOn){
        glCallList(theList);
    }
    else{
        drawTerrain();
    }
//    float lightP2[4] = {0,0,0,0};
//    glLightfv(GL_LIGHT0, GL_POSITION, lightP2);
//    glLightfv(GL_LIGHT0, GL_POSITION, lightP);
    
    
    glLightfv(GL_LIGHT0, GL_POSITION, lightP);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseColour);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambientColour);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specularColour);

    
    
    glPopMatrix();

    
    draw_axis(4.0);
    drawTerrain();//
	drawTexture();
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

void cb_mouseclick(int button, int state, int x, int y) {
}

void cb_mousemove(int x, int y) {
}

void callback_keyboard(unsigned char key, int x, int y) {
    switch(key) {
        case 'q':
            exit(0);
        case 'f':
            //            fN = !fN;
            break;
        case 'c':
            loadHeights();
            break;
            //            clearCanvas();
        case 'j':
            //            render();
            //            resizeBrush(true);
            break;
        case 'k':
            //            resizeBrush(false);
            break;
        case 'e':
            //            eraser();
            break;
    }
    if (key == 'f') fNorms = !fNorms;
    if(key == 'n')
        nearPlane -= 100;
    if(key == 'N')
        nearPlane += 100;
    if(nearPlane < 0)
        nearPlane = .1;
    
    if(key == 'm')
        farPlane -= 100;
    if(key == 'M')
        farPlane += 100;
    if(farPlane < 0)
        farPlane = 1000;
    
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
        
//        printf("Moved Light Up \n");
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
    
//    cb_reshap
}


int main(int argc, char** argv) {
    
	glutInit(&argc, argv);
    
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 800);
    //    glutInitWindowPosition(600, 120);
    //    glutInitWindowSize(1000, 1000);
	glutCreateWindow("Lab 3: Terrain Mapping");
	glutIgnoreKeyRepeat(true);
    
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
    loadHeights();
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
    glutKeyboardFunc(callback_keyboard);
	glutIdleFunc(cb_idle);
    
	glClearColor(0,0,0,0); // set background to black
    
	glutMainLoop();
    
	return 0;
}
