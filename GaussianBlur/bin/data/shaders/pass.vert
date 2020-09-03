#version 400

in vec4 position; // oF Default
in vec2 texcoord; // oF Default

out vec2 vTexCoord;

uniform float InverseUv;

void main(){
    if(InverseUv == 0.0){
        vTexCoord = vec2(texcoord.x, texcoord.y);
    }else{
        vTexCoord = vec2(texcoord.x, 1.0 - texcoord.y);
    }
    gl_Position = position;
}