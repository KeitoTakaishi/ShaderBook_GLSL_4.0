#version 400

layout (location = 0) in vec3 position;

out vec3 p;
out vec3 n;

uniform mat4 ModelViewProjectionMatrix;
uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

void main(){
    n = normalize(mat3(transpose(inverse(view * model))) * normalize(position.xyz));
    p = vec3(view * model * vec4(position, 1.0));
    gl_Position = proj * view * model * vec4(position, 1.0);
}