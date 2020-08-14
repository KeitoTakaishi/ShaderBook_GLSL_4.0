#version 400
precision mediump float;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;
uniform mat4 mvp;
uniform vec3 worldCameraPos;
uniform int DrawSkyBox;

in vec3 position;
in vec3 normal;
in vec4 color;
in vec2 texcoord;

//out vec3 vPosition;
//out vec3 vNormal;
//out vec3 envBoxvNormal;
//out vec4 vColor;
//out vec2 vTexCoord;
out vec3 refrectDir;

void main() {
    vec3 worldPos = (model * vec4(position, 1.0)).xyz;
    vec3 worldNormal  = (model * vec4(normal, 0.0)).xyz;
    vec3 worldView = normalize(worldCameraPos - worldPos);

    if(DrawSkyBox == 1){
        refrectDir = reflect(-worldView, worldNormal);
    }else{
        refrectDir = normalize(position);
    }
    
    gl_Position    = proj * view * model * vec4(position, 1.0);
}