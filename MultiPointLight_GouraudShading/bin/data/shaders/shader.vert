#version 400
layout (location = 0) in vec3 position;
out vec3 vColor;

// layout (std140) uniform LightInfo {
//     vec4 Position;
//     vec4 La;
//     vec4 Ld;
//     vec4 Ls;
// }Light;

// layout (std140) uniform MaterialInfo {
//     vec4 Ka;
//     vec4 Kd;
//     vec4 Ks;
//     float shininess;
// }Material;

struct LightInfo{
    vec4 Position;
    vec4 La;
    vec4 Ld;
    vec4 Ls;
};
uniform LightInfo light;

struct MaterialInfo{
    vec4 Position;
    vec4 La;
    vec4 Ld;
    vec4 Ls;
};
uniform MaterialInfo material;

uniform mat4 modelViewProjectionMatrix;
uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;


void main(){
    //vColor = vec3(Light.La.x + Material.Ka.x , Light.Ld.x + Material.Kd.x, Light.Ls.x + Material.Ks.x );
    vColor = vec3(light.La);
    gl_Position = proj * view * model * vec4(position, 1.0);
}