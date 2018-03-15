#include "mat.h"
#include "Camera.h"

Camera::Camera(float x, float y, float z, bool cam1){
    u = 0;
    n = 0;
    v = 0;
    s = 0.7;
    eye = { x, y, z, 1};
    if(cam1){
        up = { 0, 1, 0, 0 };
        at = { 0, 0, -1, 0 };
    } else {
        up = { 0, 0, -1, 0 };
        at = { 0, -1, 0, 0 };
    }
    projection_matrix = Perspective(65, 1, 1, 100);
    camera_matrix = LookAt(eye, at+eye, up);
    orthographic = false;
}

void Camera::pitchDown(){
    u += 1;
    move();
}

void Camera::pitchUp(){
    u -= 1;
    move();
}
void Camera::yawClockwise(){
    v += 1;
    move();
}

void Camera::yawCClockwise(){
    v -= 1;
    move();
}

void Camera::rollClockwise(){
    n += 1;
    move();
}

void Camera::rollCClockwise(){
    n -= 1;
    move();
}

void Camera::moveTowards(){
    eye += at*s;
    move();
}

void Camera::moveAway(){
    eye -= at*s;
    move();
}

void Camera::moveRight(){
    eye += normalize(cross(at, up))*s;
    move();
}

void Camera::moveLeft(){
    eye -= normalize(cross(at, up))*s;
    move();
}

void Camera::changePerspective(){
    if (orthographic) {
        projection_matrix = Perspective(65,1,1,100);
    } else {
        projection_matrix = Ortho(-1, 1, -1, 1, 1.0, 3.0);
    }
    orthographic = !orthographic;
    move();
}

void Camera::move(){
    mat4 update = RotateX(u)*RotateY(n)*RotateZ(v);
    vec4 mat = normalize(update*at) + eye;
    vec4 mup = normalize(update*up);
    camera_matrix = LookAt(eye, mat, mup);
}

Camera::~Camera(){
    
}
