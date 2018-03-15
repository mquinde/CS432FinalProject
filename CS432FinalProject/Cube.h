#ifndef __CUBE_H__
#define __CUBE_H__

#include "Angel.h"
#include "Drawable.h"
#include "Camera.h"
#include "Light.h"
#include <string>
#include <vector>

using namespace std;

class Cube: public Drawable{


public:
	Cube();
	~Cube();
    void setMaterial(vec4, vec4, vec4, float);
    void draw(Camera*, vector<Light>, vector<bool>);
    
private:
    static const unsigned int numVertices = 6 * 2 * 3;
	void buildCube();
	void makeQuad(int, int, int, int);
	GLuint vPosition;
	GLuint vColor;
	GLuint mmLoc;
    //shader variable locations
    GLuint vpos, npos;
    GLuint mmpos, cmpos, pmpos;
    GLuint diffuse_loc, spec_loc, ambient_loc, alpha_loc;
    //material properties
    vec4 diffuse, specular, ambient;
    float shine;
    unsigned int index;
    vec4 vertexLocations[numVertices];
    vec3 vertexNormals[numVertices];

	vec4 vertices[8] = { vec4(-0.5,-0.5,0.5,1),vec4(-0.5,0.5,0.5,1),vec4(0.5,0.5,0.5,1),vec4(0.5,-0.5,0.5,1),
		vec4(-0.5,-0.5,-0.5,1),vec4(-0.5,0.5,-0.5,1),vec4(0.5,0.5,-0.5,1),vec4(0.5,-0.5,-0.5,1) };
	
	
};

#endif
