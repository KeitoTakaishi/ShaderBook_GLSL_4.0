#version 400

in vec3 position;

out vec3 Position;
out vec3 Normal;
out vec4 ShadowCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

//shadow
uniform mat4 shadowMat;//Bias*Proj_l*View_l*Mode

void main(){
    Position = (view * model * vec4(position.xyz, 1.0)).xyz;
    Normal = normalize(mat3(transpose(inverse(view * model))) * normalize(position.xyz));
    
    ShadowCoord = shadowMat * vec4(position, 1.0);
    gl_Position = proj * view * model * vec4(position.xyz, 1.0);
}