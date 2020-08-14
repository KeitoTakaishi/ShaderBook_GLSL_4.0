#version 400
precision mediump float;


uniform samplerCube	CubeMap;
uniform int DrawSkyBox;
uniform float refrectFactor;
uniform float transparent;
uniform vec3 materialColor;

/*
in vec3 vPosition;
in vec3 vNormal;
in vec3 envBoxvNormal;
in vec4 vColor;
in vec2 vTexCoord;
*/
in vec3 reflectDir;
in vec3 refractDir;


out vec4 outputColor;

void main(){    
    if(DrawSkyBox == 1){
        //Cube
        vec4 reflectColor  = texture(CubeMap, reflectDir);
        vec4 refractColor  = texture(CubeMap, refractDir);
        reflectColor = reflectColor * vec4(materialColor, 1.0);
        outputColor = vec4(mix(reflectColor, refractColor, refrectFactor));
        outputColor.a = transparent;
    }else{
        //Box
       vec4 reflectColor  = texture(CubeMap, reflectDir);
       outputColor = reflectColor;
    }
}