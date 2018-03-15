#ifndef __DRAWABLE_H__
#define __DRAWABLE_H__
#include "Angel.h"
#include "Camera.h"
#include "Light.h"
#include <cassert>
#include <vector>

using namespace std;

class Drawable {
protected:
    GLuint program;
    GLuint VAO;
    GLuint VBO;
    vec4 color;

public:
	virtual void draw(Camera*, vector<Light>, vector<bool>)=0;
	void setModelMatrix(mat4 mm) { modelmatrix = mm; }
	static unsigned char* ppmRead(char* filename, int* width, int* height);
    virtual ~Drawable()=0;
    mat4 modelmatrix;
};

#endif
