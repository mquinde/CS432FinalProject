#include "Sphere.h"

Sphere::~Sphere(){
}

Sphere::Sphere() {
    index = 0;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    build();
    program = InitShader("../vshaderLighting_v150.glsl", "../fshaderLighting_v150.glsl");
    glUseProgram(program);
    vpos = glGetAttribLocation(program, "vPosition");
    npos = glGetAttribLocation(program, "vNormal");
    mmpos = glGetUniformLocation(program, "model_matrix");
    cmpos = glGetUniformLocation(program, "cam_matrix");
    pmpos = glGetUniformLocation(program, "proj_matrix");
    diffuse_loc = glGetUniformLocation(program, "matDiffuse");
    spec_loc = glGetUniformLocation(program, "matSpecular");
    ambient_loc = glGetUniformLocation(program, "matAmbient");
    alpha_loc = glGetUniformLocation(program, "matAlpha");
    
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexLocations)+sizeof(vertexNormals), NULL,
                 GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertexLocations), vertexLocations);
    glBufferSubData(GL_ARRAY_BUFFER, 0+sizeof(vertexLocations), sizeof(vertexNormals),
                    vertexNormals);
    glEnableVertexAttribArray(vpos);
    glVertexAttribPointer(vpos, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
    glEnableVertexAttribArray(npos);
    glVertexAttribPointer(npos, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(vertexLocations)));
    
    
}

void Sphere::build() {
    sqrt2 = (float)sqrt(2.0);
    sqrt6 = (float)sqrt(6.0);
    
    index = 0;
    
    tetrahedron(4);
    
}

void Sphere::tetrahedron(int count){
    vec4 v[4] = {
        vec4(0,0,1,1),
        vec4(0,2*sqrt2/3,-1.0f/3.0f,1),
        vec4(-sqrt6/3.0f,-sqrt2/3.0f,-1.0f/3.0f,1.0f),
        vec4(sqrt6/3.0f,-sqrt2/3.0f,-1.0f/3.0f,1.0f)
    };
    
    divideTriangle(v[0], v[1], v[2], count);
    divideTriangle(v[3], v[2], v[1], count);
    divideTriangle(v[0], v[3], v[1], count);
    divideTriangle(v[0], v[2], v[3], count);
}

void Sphere::divideTriangle(vec4 a, vec4 b, vec4 c, int count){
    if(count>0){
        vec4 v1 = unit(a+b);
        v1.w = 1.0;
        vec4 v2 = unit(a+c);
        v2.w = 1.0;
        vec4 v3 = unit(b+c);
        v3.w = 1.0;
        
        divideTriangle(a, v2, v1, count - 1);
        divideTriangle(c, v2, v3, count - 1);
        divideTriangle(b, v3, v1, count - 1);
        divideTriangle(v1, v3, v2, count - 1);
        
    } else {
        triangle(a,b,c);
    }
}

vec4 Sphere::unit(vec4 p) {
    float len = p.x*p.x + p.y*p.y + p.z*p.z;
    vec4 t;
    if(len > DivideByZeroTolerance){
        t = p/sqrt(len);
        t.w = 1.0;
    }
    return t;
}

void Sphere::triangle(vec4 ai, vec4 bi, vec4 ci){
    vec3 a = vec3(ai.x,ai.y,ai.z);
    vec3 b = vec3(bi.x,bi.y,bi.z);
    vec3 c = vec3(ci.x,ci.y,ci.z);
    
    vec3 N = normalize(cross(b-a,c-a));
    
    
    vertexLocations[index] = a;
    vertexNormals[index] = N;
    index++;
    
    vertexLocations[index] = b;
    vertexNormals[index] = N;
    index++;
    
    vertexLocations[index] = c;
    vertexNormals[index] = N;
    index++;
    
}
void Sphere::setMaterial(vec4 a, vec4 d, vec4 s, float sh) {
    diffuse = d;
    specular = s;
    ambient = a;
    shine = sh;
}

void Sphere::draw(Camera *cam, vector<Light> lights, vector<bool> enabled) {
    glBindVertexArray(VAO);
    glUseProgram(program);
    glUniformMatrix4fv(mmpos, 1, GL_TRUE, modelmatrix);
    glUniformMatrix4fv(cmpos, 1, GL_TRUE, cam->camera_matrix);
    glUniformMatrix4fv(pmpos, 1, GL_TRUE, cam->projection_matrix);
    glUniform4fv(diffuse_loc, 1, diffuse);
    glUniform4fv(spec_loc, 1, specular);
    glUniform4fv(ambient_loc, 1, ambient);
    glUniform1f(alpha_loc, shine);
    GLuint enabled_loc = glGetUniformLocation(program, "enabled1");
    if(enabled[0]){
        glUniform1i(enabled_loc, GLuint(1));
        GLuint light_loc = glGetUniformLocation(program, "lightPos1");
        glUniform4fv(light_loc, 1, lights[0].getPosition());
        GLuint ambient_loc2 = glGetUniformLocation(program, "lightAmbient1");
        glUniform4fv(ambient_loc2, 1, lights[0].getAmbient());
        GLuint diffuse_loc2 = glGetUniformLocation(program, "lightDiffuse1");
        glUniform4fv(diffuse_loc2, 1, lights[0].getDiffuse());
        GLuint specular_loc2 = glGetUniformLocation(program, "lightSpecular1");
        glUniform4fv(specular_loc2, 1, lights[0].getSpecular());
    } else {
        glUniform1i(enabled_loc, GLuint(0));
    }
    enabled_loc = glGetUniformLocation(program, "enabled2");
    if(enabled[1]){
        glUniform1i(enabled_loc, GLuint(1));
        GLuint light_loc = glGetUniformLocation(program, "lightPos2");
        glUniform4fv(light_loc, 1, lights[1].getPosition());
        GLuint ambient_loc2 = glGetUniformLocation(program, "lightAmbient2");
        glUniform4fv(ambient_loc2, 1, lights[1].getAmbient());
        GLuint diffuse_loc2 = glGetUniformLocation(program, "lightDiffuse2");
        glUniform4fv(diffuse_loc2, 1, lights[1].getDiffuse());
        GLuint specular_loc2 = glGetUniformLocation(program, "lightSpecular2");
        glUniform4fv(specular_loc2, 1, lights[1].getSpecular());
    } else {
        glUniform1i(enabled_loc, GLuint(0));
    }
    glDrawArrays(GL_TRIANGLES,0, numVertices);
    
}
