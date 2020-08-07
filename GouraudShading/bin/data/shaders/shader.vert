#version 410

layout (location = 0) in vec3 position;
//layout (location = 1) in vec3 normal;

 out vec3 vColor;

uniform mat4 modelViewProjectionMatrix;
uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

uniform vec3 _LightPos;
uniform vec3 _La;
uniform vec3 _Ld;
uniform vec3 _Ls;
uniform vec3 _Ka;
uniform vec3 _Kd;
uniform vec3 _Ks;
uniform float _shininess;
uniform int _debug;

void main(){
    vec3 tnormal = normalize(position);
    tnormal = mat3(transpose(inverse(view * model))) * tnormal;
    vec4 eyeCoord = view * model * vec4(position, 1.0);

    vec3 s = normalize(_LightPos - eyeCoord.xyz);//vertex to Light
    vec3 v = normalize(-eyeCoord.xyz);//Vertex in eyeSpace to camera  
    vec3 r = reflect(-s, tnormal);

    vec3 ambient = _La * _Ka;
    
    float sDotN = max(dot(s, tnormal), 0.0);
    vec3 diffuse = _Ld * _Kd * sDotN;

    vec3 spec = vec3(0.0);
    if(sDotN > 0.0){
        spec = _Ls * _Ks * pow(max(dot(r, v), 0.0), _shininess);
    }


    if(_debug == 0){
        vColor = vec3(ambient + diffuse + spec);
    }else{
        vColor = vec3(tnormal);
    }
    
    
    //gl_Position = modelViewProjectionMatrix * vec4(position, 1.0);
    gl_Position = proj * view * model * vec4(position, 1.0);
}