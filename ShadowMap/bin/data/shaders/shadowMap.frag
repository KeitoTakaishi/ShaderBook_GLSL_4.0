#version 400

in vec3 Position;
in vec3 Normal;
in vec4 ShadowCoord;

layout(location = 0) out vec4 FragColor;

uniform mat4 m, v, p;
//lighting
uniform vec3 lightPos;
//shadow
//uniform mat4 s;//Bias*Proj_l*View_l*Mode
uniform sampler2D shadowMap;
uniform vec2 uRes;
void main(){

    //depth map
	float depta = 0.00001;
	float depth = textureProj(shadowMap, ShadowCoord).r + depta;
    if(ShadowCoord.z/ShadowCoord.w > depth){
		depth = 0.0;
	}else{
		depth = 1.0;
	}


	//out of frustrum
	vec2 uv = ShadowCoord.xy / ShadowCoord.w;
	if(uv.x < 0.0 || uv.x > 1.0 || uv.y < 0.0 || uv.y > 1.0){
		depth = 1.0;
	}

    vec3 diffuse = vec3(dot(normalize(lightPos), Normal));
    
	

    vec4 c = vec4(1.0);
    c.rgb = diffuse*depth;
    FragColor = c;

   
}   