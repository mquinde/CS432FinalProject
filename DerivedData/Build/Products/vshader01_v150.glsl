#version 150

in vec4 vPosition;
in vec3 vNormal;

out vec3 fN;
out vec3 fE;
out vec3 fL;

uniform mat4 model_matrix;
uniform mat4 cam_matrix;
uniform mat4 proj_matrix;

uniform vec4 LightPosition;



void main()
{
    vec3 pos = (cam_matrix*model_matrix*vPosition).xyz;
    
    vec3 lightPosInCamera = (cam_matrix*LightPosition).xyz;
    
    fN = normalize(cam_matrix*model_matrix*vec4(vNormal,0)).xyz;
    fE = normalize(vec3(0,0,0)-pos);
    fL = normalize(lightPosInCamera-pos);
    
    gl_Position = proj_matrix*cam_matrix*model_matrix*vPosition;  //assign the vertex position to the vPosition attribute multiplied by the model matrix
}
