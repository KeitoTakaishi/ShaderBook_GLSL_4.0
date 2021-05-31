#version 400


in vec2 vTexCoord;
layout (location = 0) out vec4 FragColor;


uniform sampler2DRect tex0;
uniform vec2 uRes;

void main(){
    float depth = texture(tex0, vTexCoord * uRes).r;
     
    FragColor = vec4(vec3(depth), 1.0);
}

