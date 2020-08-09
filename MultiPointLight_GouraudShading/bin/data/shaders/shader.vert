#version 460
layout (location = 0) in vec3 position;
out vec3 vColor;

#define LIGHT_NUM 7

struct LightInfo{
    vec3 position;
    vec3 intensity;
};
uniform LightInfo lightInfo[LIGHT_NUM];

layout (std140, packed) uniform MaterialInfo {
    vec4 Ka;
    vec4 Kd;
    vec4 Ks;
    float shininess;
}Material;



uniform mat4 modelViewProjectionMatrix;
uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;
uniform int type;
vec3 ads( int i, vec4 p, vec3 n){
    vec3 s = normalize(lightInfo[i].position - p.xyz);
    vec3 v = normalize(-vec3(p));
    vec3 r = reflect(-s, n); 
    vec3 I = lightInfo[i].intensity;

    return I * (Material.Ka.xyz + 
    Material.Kd.xyz * max(dot(s, n), 0.0)) + 
    Material.Ks.xyz * pow( max(dot(r, v), 0.0), Material.shininess);

}

void main(){
    vec3 tnorm;
    vec4 eyeCoord;
    if(type == 0){
        tnorm = normalize(mat3(transpose(inverse(view * model))) * normalize(position.xyz));
    }else{
        tnorm = vec3(0.0 , 0.0,-1.0);
    }
    eyeCoord = view * model * vec4(position, 1.0);
    
    vColor = vec3(0.0);
    for(int i = 0; i < LIGHT_NUM; i++){
        vColor += ads(i, eyeCoord, tnorm);
    }
    
    gl_Position = proj * view * model * vec4(position, 1.0);
}