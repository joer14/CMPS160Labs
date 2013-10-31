/**
* CMPS 160L (Fall 2011)
* Lab 2: Animated Animal
*/

#ifndef UTIL_H
#define UTIL_H

extern enum cam_mode {DEFAULT, FRONT, SIDE, TOP, ANGLE};

void camera();

void set_cam(cam_mode newmode);

void draw_string( float x, float y, float z, char *txt );

void draw_axis(float len);

#endif