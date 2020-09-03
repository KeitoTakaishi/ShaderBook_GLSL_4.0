#version 400
//#include "lighting.glsl"

in vec3 Position;
in vec3 Normal;
in vec2 vTexCoord;
layout (location = 0) out vec4 FragColor;

uniform vec3 Ka;
uniform vec3 Kd;
uniform vec3 Ks;
uniform float shininess;
uniform vec3 lightPosition;
uniform vec3 lightIntensity;

uniform sampler2DRect tex0;
uniform vec2 uRes;
uniform float EdgeThreshold;

subroutine vec4 RrenderPassType();
subroutine uniform RrenderPassType RenderPass;

vec3 debug(){
    return vec3(1.0, 0.0, 0.0); 
}


vec3 phongMmodel(vec3 norDir, vec3 eyeDir, vec3 lightDir){
     vec3 r = reflect(-lightDir, norDir);//reflection
     
     
     return lightIntensity * 
        (Ka + 
        Kd * max(dot(lightDir, norDir), 0.0)) + 
        Ks * pow( max(dot(r, eyeDir), 0.0), shininess);
        
}

float luma(vec4 c){
    return 0.2126 * c.r + 0.7152 * c.g + 0.0722 * c.b;
}

subroutine (RrenderPassType)
vec4 LightingPass(){
    vec3 n = normalize(Normal);
    vec3 lightDir = normalize(lightPosition - Position);
    vec3 eyeDir = normalize(-Position);
    return vec4(phongMmodel(n, eyeDir, lightDir).rgb, 1.0);
}


subroutine (RrenderPassType)
vec4 EdgeDetectionPass(){
    vec2 uv = vTexCoord * uRes;
    vec2 d = vec2(1.0, 1.0);

    float s00 = luma(texture(tex0, uv + vec2(-d.x, d.y)));
    float s10 = luma(texture(tex0, uv + vec2(-d.x, 0.0)));
    float s20 = luma(texture(tex0, uv + vec2(-d.x, -d.y)));
    float s01 = luma(texture(tex0, uv + vec2(0.0, d.y)));
    float s21 = luma(texture(tex0, uv + vec2(0.0, -d.y)));
    float s02 = luma(texture(tex0, uv + vec2(d.x, d.y)));
    float s12 = luma(texture(tex0, uv + vec2(d.x, 0.0)));
    float s22 = luma(texture(tex0, uv + vec2(d.x, -d.y)));

    float sx = s00 + 2.0 + s10 + s20 - (s02 + 2.0 * s12 + s22);
    float sy = s00 + 2.0 * s01 + s02 - (s20 + 2.0 * s21 + s22);
    float dist = sx * sx + sy * sy;

    
    /*
    float edge = 0.0;
    if(dist > EdgeThreshold){
        edge = 1.0;
    }else{
        edge = 0.0;
    }
    */
    float edge = step(EdgeThreshold, dist);
    
    
    
    return vec4(vec3(edge), 1.0);
    


    return texture(tex0, vTexCoord * uRes);
}

void main(){
    vec4 col = vec4(1.0);
    col = RenderPass();
    FragColor = col;
}