#version 400
out vec4 fragColor;

subroutine vec3 FragModel();
subroutine uniform FragModel fragModel;


subroutine(FragModel)
vec3 redPass(){
    return vec3(1.0, 0.0, 0.0);
}

subroutine(FragModel)
vec3 greenPass(){
    return vec3(0.0, 1.0, 0.0);
}

subroutine(FragModel)
vec3 bluePass(){
    return vec3(0.0, 0.0, 1.0);
}

void main(){
    vec3 c = fragModel();
    fragColor = vec4(c, 1.0);
}
