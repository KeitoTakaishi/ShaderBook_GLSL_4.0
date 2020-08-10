#version 400

in vec3 p;
in vec3 n;


uniform vec3 lightPosition;
uniform vec3 lightIntensity;
uniform vec3 Ka;
uniform vec3 Kd;
uniform vec3 Ks;
uniform float shininess;
uniform int optimize;
layout (location = 0) out vec4 FragColor;


vec3 ads(){
    vec3 _n = normalize(n);
    vec3 s = normalize(lightPosition - p.xyz);
    vec3 v = normalize(-vec3(p));

    if(optimize == 0){
        vec3 r = reflect(-s, _n); 
    
        return lightIntensity * (Ka + 
        Kd * max(dot(s, n), 0.0)) + 
        Ks * pow( max(dot(r, v), 0.0), shininess);
    }else{
        vec3 h = normalize(v + s);
        return lightIntensity * (Ka + 
        Kd * max(dot(s, n), 0.0)) + 
        Ks * pow( max(dot(h, n), 0.0), shininess);
    }

}


void main(){
    FragColor = vec4(ads(), 1.0);
}

