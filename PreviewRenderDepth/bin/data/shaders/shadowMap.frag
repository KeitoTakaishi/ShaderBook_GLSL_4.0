#version 400

in vec3 Position;
in vec3 Normal;
in vec4 ShadowCoord;

layout(location = 0) out vec4 FragColor;

uniform mat4 m, v, p;
//lighting
uniform vec3 lightPos;
//shadow
//uniform mat4 s;//Bias*Proj_l*View_l*Mode
uniform sampler2DRect shadowMap;
uniform vec2 uRes;

void main(){
    
	float diff = dot(vec3(0.3, 0.8, 0.3), Normal);
    FragColor = vec4(vec3(diff), 1.0);
}   