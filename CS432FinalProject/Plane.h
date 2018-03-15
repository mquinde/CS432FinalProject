//
//  Plane.hpp
//  CS432A5
//
//  Created by Mariana Quinde Garcia on 3/4/18.
//  Copyright © 2018 Mariana Quinde Garcia. All rights reserved.
//

#ifndef Plane_h
#define Plane_h

#include "Angel.h"
#include "Drawable.h"
#include "Camera.h"
#include "Light.h"
#include <string>
#include <vector>

using namespace std;

class Plane:public Drawable {
public:
    Plane();
    void setMaterial(vec4, vec4, vec4, float);
    void draw(Camera*, vector<Light>, vector<bool>);
    ~Plane();
private:
    static const unsigned int numVertices = 6;
    vec4 vertexLocations[numVertices] = { vec4(10, -1, 10, 1), vec4(-10, -1, 10, 1), vec4(10, -1, -10, 1), vec4(10, -1, -10, 1), vec4(-10, -1, 10, 1), vec4(-10, -1, -10, 1)};
    vec3 vertexNormals[numVertices];
    //shader variable locations
    GLuint vpos, npos;
    GLuint mmpos, cmpos, pmpos;
    GLuint diffuse_loc, spec_loc, ambient_loc, alpha_loc;
    //material properties
    vec4 diffuse, specular, ambient;
    float shine;
    unsigned int index;
    void setNormals(vec4, vec4, vec4);
    
};
#endif /* Plane_hpp */
