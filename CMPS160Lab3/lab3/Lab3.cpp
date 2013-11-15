
// Lab3.cpp : Terrain Mapping
//

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

canvas_t terrain;
canvas_t skin;
GLuint texture;

float farPlane, nearPlane;


float ambientColour[3];
float lightPosition[4];
float diffuseColour[3];
float** hMap;

//GLuint texture;
GLuint terrainDL;

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
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
    
	glDisable(GL_TEXTURE_2D);
}



void loadHeights(){
    
//    printf("loading heights\n");
//    hMap = new float*[terrain.height];
//    
//    //create array for hMap
//    
//    for(int i = 0; i < terrain.height; i++){
//        hMap[i] = new float[terrain.width];
//    }
//    
//    printf("loading heights\n");
//    //creating hMap such that hMap[z][x]=y
//    
//    for(int z = 0; z < terrain.height; z++){
//        for(int x = 0; x < terrain.width; x++){
//            pixel_t pixel = PIXEL(terrain, x, z);
//            float y = (((float)RED(pixel)) / 255.0f) * 100;
//            //          printf ("x: %d red: %f z: %d\n", x,y,z);
//            hMap[z][x] = y;
//        }
//    }
//    
//    printf("done loading heights\n");
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
    
//    printf("z: %d x: %d\n",z, x);
  
    float v1[3]= {(float)x,float(RED(PIXEL(terrain, x, z))), (float)z};
    float v2[3]= {(float)x,float(RED(PIXEL(terrain, x, z+1))), (float)z+1};
    float v3[3]= {(float)x+1,float(RED(PIXEL(terrain, x+1, z))), (float)z};
    float v4[3]= {(float)x+1, float(RED(PIXEL(terrain, x+1, z+1))), (float)z+1};
    
    //float(RED(PIXEL(terrain, x, z)))
    float e1[3];
    float e2[3];
    if (!upper){
        diff(e1,v2,v1);
        diff(e2,v3,v1);
        cross(result,e1,e2);
        normalize(result, result);
    }else{
        diff(e1,v2,v4);
        diff(e2,v3,v4);
        cross(result,e1,e2);
        normalize(result, result);
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

void drawTerrain(){
    
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture);
//    //for maping the texture on
//    glTranslatef(-(float)(terrain.width - 1) / 2, 0, -(float)(terrain.height -1) / 2);

    float the_normal[3];//
    
    glBegin(GL_TRIANGLES);
    
    for(int z = 0; z < terrain.height-1; z++){
        for(int x = 0; x < terrain.width-1; x++){
        
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
    }
    
    glEnd();
    
    glDisable(GL_TEXTURE_2D);
//    printf("Created Triangle Strip\n");

    
}



void rotateCamera(void)
{
    glRotatef(xRotation, 1, 0, 0);
    glRotatef(yRotation, 0, 1, 0);
    glTranslatef(-xposition, -yposition, -zposition);
}


void cb_display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
    gluLookAt(200,200,200,
              0,0,0,
              0,1,0);
    rotateCamera();
    // Rotate along y-axis
	if (is_spinning) {
		glRotatef(spinAngle, 0, 1, 0);
		spinAngle++;
	}
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
    gluPerspective(90.0, aspectRatio, .1, 1000); // necessary to preserve aspect ratio
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
    if(key == 'j')
        nearPlane -= 2;
    if(key == 'k')
        nearPlane += 2;
    if(nearPlane < 0)
        nearPlane = .1;
    
    if(key == 'n')
        farPlane -= 2;
    if(key == 'm')
        farPlane += 2;
    if(farPlane < 0)
        farPlane = 50;
    
    
    if(key == 'f')
    {
        xRotation += 1;
        if(xRotation > 360) xRotation -= 360;
    }
    
    if(key == 'g')
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
    
    
}


int main(int argc, char** argv) {
    
	glutInit(&argc, argv);
    
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
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
    
	//terrain->drawTerrain();
    loadHeights();
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glEnable (GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	
    nearPlane = .1;
    farPlane = 1000;
    
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_NORMALIZE);
//    createTerrainDisplayList();
    int cam_pos[3] = {0,0,15};
    int center_pos[3] = {0,0,0};
	
	glutDisplayFunc(cb_display);
	glutReshapeFunc(cb_reshape);
    glutKeyboardFunc(callback_keyboard);
	glutIdleFunc(cb_idle);
    
	glClearColor(0,0,0,0); // set background to black
    
	glutMainLoop();
    
	return 0;
}
