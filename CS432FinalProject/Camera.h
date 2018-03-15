#ifndef __CAMERA_H__
#define __CAMERA_H__
#include "Angel.h"

class Camera {
    
public:
    Camera(float x, float y, float z, bool cam1);
    ~Camera();
    void pitchDown();
    void pitchUp();
    void yawClockwise();
    void yawCClockwise();
    void rollClockwise();
    void rollCClockwise();
    void moveTowards();
    void moveAway();
    void moveRight();
    void moveLeft();
    void changePerspective();
    mat4 projection_matrix;
    mat4 camera_matrix;
    vec4 eye,at,up;
    
private:
    GLfloat u,v,n,s;
    void move();
    bool orthographic;
    
};

#endif
