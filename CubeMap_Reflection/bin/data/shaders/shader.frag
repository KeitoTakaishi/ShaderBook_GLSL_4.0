#version 400
precision mediump float;


uniform samplerCube	CubeMap;
uniform int DrawSkyBox;
uniform float reflectFactor;
uniform vec3 materialColor;
/*
in vec3 vPosition;
in vec3 vNormal;
in vec3 envBoxvNormal;
in vec4 vColor;
in vec2 vTexCoord;
*/
in vec3 refrectDir;
in vec3 vNormal;

out vec4 outputColor;

void main(){    
    if(DrawSkyBox == 1){
        //Cube
        vec4 envColor  = texture(CubeMap, refrectDir);
        outputColor = vec4( vec3(mix(materialColor, envColor.xyz, reflectFactor)), 1.0);
        //outputColor = vec4(vec3(vNormal), 1.0);
    }else{
        //Box
       vec4 envColor  = texture(CubeMap, refrectDir);
       outputColor = envColor;
    }
}