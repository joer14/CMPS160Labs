// Lab3.cpp : Terrain Mapping
//

#include <stdlib.h>
#include <stdio.h>
#include <glut/glut.h>
#include <math.h>

#include "ppm_canvas.h"
#include "util.h"

#define PI 3.14159265

float xpos = 0, ypos = 0, zpos = 0;
float xrot, yrot = 0;
bool keyState[256] = { false };
int windowWidth, windowHeight;

canvas_t terrain;
canvas_t skin;
GLuint texture;

float farPlane, nearPlane;

float lightPosition[4];
float diffuseColour[3];
float ambientColour[3];
float** hMap;

void drawTexture() {
	int x, z;
	
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture);
	
	gluLookAt(0,0,15,0,0,0,0,1,0);
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
    
    printf("loading heights\n");
    hMap = new float*[terrain.height];
    
    //create array for hMap
    
    for(int i = 0; i < terrain.height; i++){
        hMap[i] = new float[terrain.width];
    }
    
    printf("loading heights\n");
    //creating hMap such that hMap[z][x]=y
    
    for(int z = 0; z < terrain.height; z++){
        for(int x = 0; x < terrain.width; x++){
            pixel_t pixel = PIXEL(terrain, x, z);
            float y = (((float)RED(pixel)) / 255.0f) * 100;
//          printf ("x: %d red: %f z: %d\n", x,y,z);
            hMap[z][x] = y;
        }
    }
    
    printf("done loading heights\n");
}
//face normal is regular - computes the cross product between 2 given vectors

 //vertex normal is the average of the 6 triangles that touch the given triangle
//void compute

//computers the normal for a given triangle
//
void cross(float *cResult, float a[3], float b[3]){
    cResult[0] = (a[2]*b[3])-(a[3]*b[2]);
    cResult[1] = a[2]*b[3] - a[1]*b[3];
    cResult[2] = a[1]*b[2] - a[2]*b[1];
};

void compute_normal(float *result, int x, int z, bool upper) {
    // compute the normal
    
    
    float out[3];
    float left[3];
    float right[3];
    float inner[3];

    if (z > 0) {
        out[0] = 0.0f;
        out[1] = hMap[z - 1][x] - hMap[z][x];
        out[2] = -1.0f;
    }
    if (z < terrain.height - 1) {
        inner[0] = 0.0f;
        inner[1] =  hMap[z + 1][x] - hMap[z][x];
        inner[2] = 1.0f;
    }
    if (x > 0) {
        left[0] = -1.0f;
        left[1] = hMap[z][x - 1] - hMap[z][x];
        left[2] = 0.0f;
    }
    if (x < terrain.width - 1) {
        right[0] = 1.0f;
        right[1] = hMap[z][x + 1] - hMap[z][x];
        right[2] = 0.0f;
    }
    float outLeftResult[3];
    float leftInResult[3];
    float inRightResult[3];
    float rightOutResult[3];
    
//    result = aResult;

    float sum[3];
    if(x > 0 && z > 0){
        cross(outLeftResult,out,left);
    }else {
        outLeftResult[0] = outLeftResult[1] = outLeftResult[2] = 0.0f;
    }
    
    if(x > 0 && z < terrain.height -1){
        cross(leftInResult,left,inner);
    }else {
        leftInResult[0]=leftInResult[1]=leftInResult[2]=0;
    }        
    if(x < terrain.width && z < terrain.height - 1){
        cross(inRightResult,inner,right);
    }else {
        inRightResult[0]=inRightResult[1]=inRightResult[2]=0;
    }
    if(x < terrain.width && z > 0){
        cross(rightOutResult,right,out);
    }else {
        rightOutResult[0]=rightOutResult[1]=rightOutResult[2]=0;
    };
    sum[0] = outLeftResult[0]+leftInResult[0]+inRightResult[0]+rightOutResult[0];
    sum[1] = outLeftResult[1]+leftInResult[1]+inRightResult[1]+rightOutResult[1];
    sum[2] = outLeftResult[2]+leftInResult[2]+inRightResult[2]+rightOutResult[2];
    result = sum;
        
        //    if(upper){
        //        cross(cResult, left, inner);
        //        cross(aResult, cResult, right);
        //    }
        //    else {
        //        cross(cResult, left, out);
        //        cross(aResult, cResult, right);
        //    }

        
    
//    //x,y,z X x,y,z+1
//    float y = hMap[z][x];
//    result[0] = y*(z+1)-z*y;
//    result[1] = z*x - x*(z+1);
//    result[2] = x*y - y*x;
    
//    //x,y,z X x+1, y, z+1
//    float y = hMap[z][x];
//    result[0] = y*(z+1)-z*y;
//    result[1] = z*(x+1) - x*(z+1);
//    result[2] = x*y - y*(x+1);

//    if (!upper){ //x,y,z X x,y,z+1
//        float y = hMap[z][x];
//        result[0] = y*(z+1)-z*y;
//        result[1] = z*x - x*(z+1);
//        result[2] = x*y - y*x;
//    } else{
//        float y = hMap[z][x];
//        result[0] = y*(z+1)-z*y;
//        result[1] = z*(x+1) - x*(z+1);
//        result[2] = x*y - y*(x+1);
//    }
    
//    y2 = hmAp[
    
//    ///normal x-value goes here;
//    result[1] = //normal y-value goes here;
//    result[2] = //normal z-value goes here;
}

void drawTerrain(){
    //create triangle strip for hMap[z][x]=y
    
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTranslatef(-(float)(terrain.width - 1) / 2, 0, -(float)(terrain.height -1) / 2);
    
    float the_normal[3];//
    for(int z = 0; z < terrain.height-1; z++){
        for(int x = 0; x < terrain.width-1; x++){
            glBegin(GL_TRIANGLE_STRIP);
            compute_normal(the_normal, x, z, true);
            
            glNormal3f(the_normal[0], the_normal[1], the_normal[2]);
            
            glTexCoord2f((float)(x) / terrain.width, (float)(z) / terrain.height);
            glVertex3f(x, hMap[z][x], z);
            
//            normal = normals[z+1][x];
            compute_normal(the_normal, x, z+1, true);
            glNormal3f(the_normal[0], the_normal[1], the_normal[2]);
            glTexCoord2f((float)(x) / terrain.width, (float)(z+1) / terrain.height);
            glVertex3f(x, hMap[z+1][x], z+1);
            
//            normal = normals[z][x+1];
            compute_normal(the_normal, x+1, z, true);
            glNormal3f(the_normal[0], the_normal[1], the_normal[2]);
            glTexCoord2f((float)(x+1) / terrain.width, (float)(z) / terrain.height);
            glVertex3f(x+1, hMap[z][x+1], z);
            
//            normal = normals[z+1][x+1];
            compute_normal(the_normal, x+1, z+1, true);
            glNormal3f(the_normal[0], the_normal[1], the_normal[2]);
            glTexCoord2f((float)(x+1) / terrain.width, (float)(z+1) / terrain.height);
            glVertex3f(x+1, hMap[z+1][x+1], z+1);
            glEnd();
            
            //float y = hMap[z][x];
//            glColor3d(1,1,1);
//            glBegin(GL_TRIANGLES);
//            
//            compute_normal(the_normal, x, z, true);
//            glNormal3f(the_normal[0], the_normal[1], the_normal[2]);
//            
//            //upper
//            
//            glTexCoord2f((float)(x) / terrain.width, (float)(z) / terrain.height);
//            glVertex3f(x, hMap[z][x], z); //x, y, z
//            
//            glTexCoord2f((float)(x) / terrain.width, (float)(z+1) / terrain.height);
//            glVertex3f(x, hMap[z+1][x], z+1);//x,y,z+1
//            
//            glTexCoord2f((float)(x+1) / terrain.width, (float)(z) / terrain.height);
//            glVertex3f(x+1, hMap[z][x+1], z);//x+1,y,z
//            
//            //lower
//            compute_normal(the_normal, x, z, false);
//            
//            glNormal3f(the_normal[0], the_normal[1], the_normal[2]);
//            
//                        glTexCoord2f((float)(x) / terrain.width, (float)(z) / terrain.height);
//            glVertex3f(x+1, hMap[z+1][x+1], z+1); //x+1, y+1, z+1
//            
//                        glTexCoord2f((float)(x) / terrain.width, (float)(z+1) / terrain.height);
//            glVertex3f(x, hMap[z+1][x], z+1);//x,y,z+1
//            
//                        glTexCoord2f((float)(x+1) / terrain.width, (float)(z) / terrain.height);
//            glVertex3f(x+1, hMap[z][x+1], z);//x+1,y,z
//            
//            
//            
////            glTexCoord2f((float)(x+1) / terrain.width, (float)(z+1) / terrain.height);
////            glVertex3f(x+1, hMap[z+1][x+1], z+1);
//            
//            glEnd();
        }
        
//        for (/*blah blah blah*/) {
//            compute_normal(the_normal, x, y, true); // computes normal for the upper triangle
//            glNormal3fv(the_normal);
//            glVertex3f(x, y, RED(PIXEL(terrain, x, y));
//                       // draw the rest of the "upper" triangle for this grid cell
//                       compute_normal(the_normal, x, y, false); // overwrites the old normal data with new numbers for the lower triangle
//                       glNormal3fv(the_normal); // updates the OpenGL current normal
//                       glVertex3f(x+1, y, RED(PIXEL(terrain, x+1, y));
//                                  // draw the rest of the "lower" triangle for this grid cell
//                                  }
    }
    glDisable(GL_TEXTURE_2D);
    printf("Created Triangle Strip\n");
}
    



void rotateCamera(void)
{
    glRotatef(xrot, 1, 0, 0);
    glRotatef(yrot, 0, 1, 0);
    glTranslatef(-xpos, -ypos, -zpos);
}

void cb_display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
    rotateCamera();
	draw_axis(4.0);
    drawTerrain();//
	drawTexture();
	glFlush();
	glutSwapBuffers(); // for smoother animation
}

void loadTextureMap(canvas_t tex) {
//	glEnable(GL_TEXTURE_2D);
//	glGenTextures(1, &texture);
//	glBindTexture(GL_TEXTURE_2D, texture);
//	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, tex.height, tex.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, tex.pixels);
//	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP );
//	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
//	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
//	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
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
	drawTexture();
	glutPostRedisplay();
}

void cb_reshape(int w, int h) {
//	windowWidth = w;
//	windowHeight = h;
//	int aspect = w/h;
//	glViewport(0, 0, w, h);
//	glMatrixMode(GL_PROJECTION);
//	glLoadIdentity();
//	gluPerspective(90.0, aspect, 0.1, 200); // necessary to preserve aspect ratio
//	glMatrixMode(GL_MODELVIEW);
//    
    
    windowWidth = w;
    windowHeight = h;
    int aspect = w/h;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(90.0, aspect, nearPlane, farPlane); // necessary to preserve aspect ratio
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
    
    if(key == 'f')
    {
        xrot += 1;
        if(xrot > 360) xrot -= 360;
    }
    
    if(key == 'g')
    {
        xrot -= 1;
        if(xrot < -360) xrot -= 360;
    }
    if(key == 'w')
    {
        float xrotrad, yrotrad;
        xrotrad = (xrot / 180 * PI);
        yrotrad = (yrot / 180 * PI);
        xpos += float(sin(yrotrad));
        ypos -= float(sin(xrotrad));
        zpos -= float(cos(yrotrad));
    }
    
    if(key == 's')
    {
        float xrotrad, yrotrad;
        xrotrad = (xrot / 180 * PI);
        yrotrad = (yrot / 180 * PI);
        xpos -= float(sin(yrotrad));
        ypos += float(sin(xrotrad));
        zpos += float(cos(yrotrad));
    }
    
    if(key == 'd')
    {
        float yrotrad;
        yrotrad = (yrot / 180 * PI);
        xpos += float(cos(yrotrad));
        zpos += float(sin(yrotrad));
    }
    
    if(key == 'a')
    {
        float yrotrad;
        yrotrad = (yrot / 180 * PI);
        xpos -= float(cos(yrotrad));
        zpos -= float(sin(yrotrad));
    }
    
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
    farPlane = 50;
    
	lightPosition[0] = 0;
	lightPosition[1] = 0;
	lightPosition[2] = 50;
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_NORMALIZE);
	
	glutDisplayFunc(cb_display);
	glutReshapeFunc(cb_reshape);
    glutKeyboardFunc(callback_keyboard);
	glutIdleFunc(cb_idle);
    
	glClearColor(0,0,0,0); // set background to black
    
	glutMainLoop();
    
	return 0;
}
