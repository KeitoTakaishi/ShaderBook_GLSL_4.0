#version 400

in vec3 position;

out vec3 Position;
out vec3 Normal;
out vec2 TexCoord;


uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;


void main(){
    Position = (view * model * vec4(position.xyz, 1.0)).xyz;
    Normal = normalize(mat3(transpose(inverse(view * model))) * normalize(position.xyz));
    gl_Position = proj * view * model * vec4(position.xyz, 1.0);
}
