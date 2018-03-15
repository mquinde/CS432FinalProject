#version 150

in vec3 fN;
in vec3 fL;
in vec3 fE;

out vec4 fColor;
uniform vec4 matAmbient, matDiffuse, matSpecular;
uniform float matAlpha;
uniform vec4 lightPos1;
uniform vec4 lightAmbient1, lightDiffuse1, lightSpecular1;
uniform int enabled1;
uniform vec4 lightPos2;
uniform vec4 lightAmbient2, lightDiffuse2, lightSpecular2;
uniform int enabled2;

vec4 getColor(vec4 lightPos, vec4 lightAmbient, vec4 lightDiffuse, vec4 lightSpecular){
    vec3 N = normalize(fN);
    vec3 E = normalize(fE);
    vec3 L = normalize(fL);
    vec3 H = normalize( L + E );
    vec4 ambient = lightAmbient*matAmbient;
    float Kd = max(dot(L,N),0.0);
    vec4 diffuse = Kd*lightDiffuse*matDiffuse;
    vec4 specular;
    if(dot(L,N)<0.0)
        specular = vec4(0,0,0,1);
    else{
        float Ks = pow(max(dot(N,H),0.0),matAlpha);
        specular = Ks*lightSpecular*matSpecular;
    }
    
    return ambient + diffuse + specular;
    
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
    
    fColor=color1+color2;
    fColor.a=1.0;
    

}

