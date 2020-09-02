#version 400

in vec2 vTexCoord;
in vec4 vProjCoord;
out vec4 fragColor;


uniform sampler2D tex;//ofDisableArbTex

void main(){
    //fragColor = vec4(texture(tex, vTexCoord));
    fragColor = vec4(texture(tex, vTexCoord));
    
    if(vProjCoord.z > 0.0){
        fragColor = textureProj(tex, vec4(vProjCoord.x, vProjCoord.y, vProjCoord.z, vProjCoord.w));
        //fragColor = vec4(vProjCoord.xy, 0.0, 1.0);
    }else{
        fragColor = vec4(0.0, 0.0, 0.0, 1.0);
    }
}
