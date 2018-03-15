//
//  Sphere.h
//  CS432A4
//
//  Created by Mariana Quinde Garcia on 2/21/18.
//  Copyright © 2018 Mariana Quinde Garcia. All rights reserved.
//

#ifndef __Sphere_H__
#define __Sphere_H__

#include "Angel.h"
#include "Drawable.h"
#include "Camera.h"
#include "Light.h"
#include <string>
#include <vector>

using namespace std;

class Sphere:public Drawable {
public:
    Sphere();
    void setMaterial(vec4, vec4, vec4, float);
    void draw(Camera*, vector<Light>, vector<bool>);
    ~Sphere();
private:
    static const unsigned int numVertices = 3072;
    vec4 vertexLocations[numVertices];
    vec3 vertexNormals[numVertices];
    //shader variable locations
    GLuint vpos, npos;
    GLuint mmpos, cmpos, pmpos;
    GLuint diffuse_loc, spec_loc, ambient_loc, alpha_loc;
    //material properties
    vec4 diffuse, specular, ambient;
    float shine;
    unsigned int index;
    void build();
    void assignGouradVertices();
    float sqrt2, sqrt6;
    void tetrahedron(int);
    void divideTriangle(vec4, vec4, vec4,int);
    void triangle(vec4, vec4, vec4);
    vec4 unit(vec4);
};
#endif
