#version 400

in vec4 position; // oF Default
in vec2 texcoord; // oF Default

out vec2 vTexCoord;


void main(){
    vTexCoord = vec2(texcoord.x, 1.0 - texcoord.y);
    gl_Position = position;
}
