/*
vec3 phongMmodel(vec3 norDir, vec3 eyeDir, vec3 lightDir){
     vec3 r = reflect(-lightDir, norDir);//reflection
     return lightIntensity * 
        (Ka + 
        Kd * max(dot(s, n), 0.0)) + 
        Ks * pow( max(dot(r, v), 0.0), shininess);

}
*/

vec3 debug(){
    return vec3(1.0, 0.0, 0.0);
}