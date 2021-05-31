#version 400

in vec3 Position;
layout (location = 0) out vec4 FragColor;

void main(){
    FragColor = vec4(normalize(Position).xyz, 1.0) ;
}