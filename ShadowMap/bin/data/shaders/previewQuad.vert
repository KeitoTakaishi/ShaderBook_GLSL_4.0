#version 400

in vec4 position; // oF Default
in vec2 texcoord; // oF Default

out vec2 vTexCoord;


uniform vec2 scale;
uniform vec2 translate;

void main(){
    vTexCoord = vec2(texcoord.x, texcoord.y);
    
    vec4 p = position;

    float s = 0.25;
    p.xy *= s;
    p.xy = p.xy + vec2(1.0-s);
    gl_Position = p;
}