#version 400

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;

out vec3 vColor;


layout (std140) uniform LightInfo {
    vec4 Position;
    vec4 La;
    vec4 Ld;
    vec4 Ls;
}Light;

layout (std140) uniform MaterialInfo {
    vec4 Ka;
    vec4 Kd;
    vec4 Ks;
    float shininess;
}Material;


uniform mat4 modelViewProjectionMatrix;
uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;
uniform int _debug;


void getEyeSpace(out vec3 norm, out vec4 pos){
    norm = normalize(mat3(transpose(inverse(view * model))) * normalize(position.xyz));
    pos = view * model * vec4(position, 1.0);
}

vec3 gouraudModel(vec4 eyeCoord, vec3 tnormal){
    vec3 s = normalize(Light.Position.xyz - eyeCoord.xyz);//vertex to Light
    vec3 v = normalize(-eyeCoord.xyz);//Vertex in eyeSpace to camera  
    vec3 r = reflect(-s, tnormal);

    vec3 ambient = Light.La.xyz *  Material.Ka.xyz;
    
    float sDotN = max(dot(s, tnormal), 0.0);
    vec3 diffuse = Light.Ld.xyz * Material.Kd.xyz * sDotN;

    vec3 spec = vec3(0.0);
    if(sDotN > 0.0){
        spec = Light.Ls.xyz * Material.Ks.xyz * pow(max(dot(r, v), 0.0), Material.shininess);
    }
    return vec3(ambient + diffuse + spec);  
}


void main(){
    vec3 tnormal;
    vec4 eyeCoord;
    getEyeSpace(tnormal, eyeCoord);


    vColor = gouraudModel(eyeCoord, tnormal);
    gl_Position = proj * view * model * vec4(position, 1.0);
}