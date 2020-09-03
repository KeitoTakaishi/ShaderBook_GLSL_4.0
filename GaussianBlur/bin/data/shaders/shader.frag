#version 400
//#include "lighting.glsl"

in vec3 Position;
in vec3 Normal;
in vec2 vTexCoord;
layout (location = 0) out vec4 FragColor;


//ADS Lighting
uniform vec3 lightPosition;
uniform vec3 lightIntensity;
uniform vec3 Ka;
uniform vec3 Kd;
uniform vec3 Ks;
uniform float shininess;

//Blur Pass
uniform sampler2DRect tex0;
uniform vec2 uRes;
uniform float pixOffSet[5] = float[](0.0, 1.0, 2.0, 3.0, 4.0);
uniform float weight[5];



subroutine vec4 RrenderPassType();
subroutine uniform RrenderPassType RenderPass;


vec3 phongMmodel(vec3 norDir, vec3 eyeDir, vec3 lightDir){
     vec3 r = reflect(-lightDir, norDir);//reflection
     
     
     return lightIntensity * 
        (Ka + 
        Kd * max(dot(lightDir, norDir), 0.0)) + 
        Ks * pow( max(dot(r, eyeDir), 0.0), shininess);
        
}

subroutine (RrenderPassType)
vec4 LightingPass(){
    vec3 n = normalize(Normal);
    vec3 lightDir = normalize(lightPosition - Position);
    vec3 eyeDir = normalize(-Position);
    return vec4(phongMmodel(n, eyeDir, lightDir).rgb, 1.0);
}


subroutine (RrenderPassType)
vec4 VertBlurPass(){
    float dy = 1.0;
    vec2 uv = vTexCoord * uRes;
    vec4 sum = texture(tex0, uv) * weight[0];

    for(int i = 0; i < 5; i++){
        sum += texture(tex0, uv + vec2(0.0, pixOffSet[i] * dy)) * weight[i];
        sum += texture(tex0, uv - vec2(0.0, pixOffSet[i] * dy)) * weight[i];
    }
    return sum;
}


subroutine (RrenderPassType)
vec4 HoriBlurPass(){
    float dx = 1.0;
    vec2 uv = vTexCoord * uRes;
    vec4 sum = texture(tex0, uv) * weight[0];

    for(int i = 0; i < 5; i++){
        sum += texture(tex0, uv + vec2(pixOffSet[i] * dx, 0.0)) * weight[i];
        sum += texture(tex0, uv - vec2(pixOffSet[i] * dx, 0.0)) * weight[i];
    }
    return sum;
}


void main(){
    vec4 col = vec4(1.0);
    col = RenderPass();
    FragColor = col;
}