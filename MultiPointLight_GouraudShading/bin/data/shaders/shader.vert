#version 460
layout (location = 0) in vec3 position;
out vec3 vColor;

#define LIGHT_NUM 5

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


void main(){
    vColor = vec3(lightInfo[0].intensity);
    gl_Position = proj * view * model * vec4(position, 1.0);
}