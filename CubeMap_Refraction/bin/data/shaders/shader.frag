#version 400
precision mediump float;


uniform samplerCube	EnvMap;
uniform int DrawSkyBox;
uniform float refrectFactor;
uniform vec3 materialColor;
/*
in vec3 vPosition;
in vec3 vNormal;
in vec3 envBoxvNormal;
in vec4 vColor;
in vec2 vTexCoord;
*/
in vec3 refrectDir;

out vec4 outputColor;

void main(){    
    if(DrawSkyBox == 1){
        //Cube
        vec4 envColor  = texture(EnvMap, refrectDir);
        outputColor = vec4( vec3(mix(materialColor, envColor.xyz, refrectFactor)), 1.0);
    }else{
        //Box
       vec4 envColor  = texture(EnvMap, refrectDir);
       outputColor = envColor;
    }
}