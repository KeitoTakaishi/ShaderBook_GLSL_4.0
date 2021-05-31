#version 400

in vec3 position;

out vec3 Position;
out vec3 Normal;
out vec4 ShadowCoord;

uniform mat4 modelViewMatrix;
uniform mat4 tempMat;

uniform mat4 shadowMatrix;
uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;
uniform int geomType;

//shadow
uniform mat4 shadowMat;//Bias*Proj_l*View_l*Mode

void main(){
    Position = (proj * view * model * vec4(position.xyz, 1.0)).xyz;
    
    if(geomType == 0){
		vec3 n = normalize(normalize(position.xyz));
		n = (model * vec4(vec3(n), 0.0)).xyz;
        Normal = normalize(n);
    }else{
		vec3 n = normalize(normalize(vec3(0.0, 1.0, 0.0)));
		//n = (model * vec4(vec3(n), 0.0)).xyz;
		Normal = normalize(n);
    }
    
    //ShadowCoord = shadowMatrix * tempMat * modelViewMatrix * vec4(position, 1.0);
    ShadowCoord = shadowMatrix  * model * vec4(position, 1.0);
    gl_Position = proj * view * model * vec4(position.xyz, 1.0);
}