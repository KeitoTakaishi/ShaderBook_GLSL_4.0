#version 400
in vec4 position;
in vec2 texcoord;

out vec2 vTexCoord;
out vec4 vProjCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;
uniform mat4 bias, pP, pVM;
void main(){
    vTexCoord = texcoord;
    vProjCoord = bias * pP * pVM * vec4(position);
    gl_Position = proj * view * model * vec4(-1.0 * position.x, -1.0 * position.y, -1.0 * position.z, position.w);
    //gl_Position = proj * view * model * vec4(position);
}
