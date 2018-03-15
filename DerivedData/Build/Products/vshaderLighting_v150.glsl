#version 150

in vec4 vPosition;	//vertex attribute for vertex position
in vec3 vNormal;

out vec4 color;  //to send to the fragment shader, interpolated along the way

uniform mat4 model_matrix;  //the model matrix to transpose vertices from object coord to world coord
uniform mat4 proj_matrix;
uniform mat4 cam_matrix;

//lighting stuff...
uniform vec4 matAmbient, matDiffuse, matSpecular;
uniform float matAlpha;
uniform vec4 lightPos1;
uniform vec4 lightAmbient1, lightDiffuse1, lightSpecular1;
uniform int enabled1;
uniform vec4 lightPos2;
uniform vec4 lightAmbient2, lightDiffuse2, lightSpecular2;
uniform int enabled2;

vec4 getColor(vec4 lightPos, vec4 lightAmbient, vec4 lightDiffuse, vec4 lightSpecular){
    float dist = 1.0;
    vec3 posInCam = (cam_matrix*model_matrix*vPosition).xyz;
    vec3 lightInCam = (cam_matrix*lightPos).xyz;
    
    vec3 L = normalize(lightInCam.xyz-posInCam);
    vec3 E = normalize(vec3(0,0,0)-posInCam);
    
    vec3 N = normalize((cam_matrix*model_matrix*vec4(vNormal,0)).xyz);
    vec3 H = normalize(L+E);
    
    vec4 ambient = lightAmbient*matAmbient;
    
    float Kd = max(dot(L,N),0.0);
    vec4 diffuse = Kd*lightDiffuse*matDiffuse;
    
    vec4 specular;
    if(dot(L,N)<0.0)
        specular = vec4(0,0,0,0);
    else{
        float Ks = pow(max(dot(N,H),0.0),matAlpha);
        specular = Ks*lightSpecular*matSpecular;
    }
    
    return (ambient + diffuse + specular)*(1/pow(dist,2));
    
}

void main()
{ 

	vec4 color1 = vec4(0,0,0,0);
    if(enabled1==1){
        color1= getColor(lightPos1, lightAmbient1, lightDiffuse1, lightSpecular1);
    }
    
    vec4 color2 = vec4(0,0,0,0);
    if(enabled2==1){
        color2= getColor(lightPos2, lightAmbient2, lightDiffuse2, lightSpecular2);
    }
    
    color=color1+color2;
    color.a=1.0;
	
	
  	gl_Position = proj_matrix*cam_matrix*model_matrix*vPosition;  //assign the vertex position to the vPosition attribute multiplied by the model matrix

}

