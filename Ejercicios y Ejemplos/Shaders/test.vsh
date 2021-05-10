#version 330

//entradas para el Mesh
layout (location = 0) in vec3 vPos;
layout (location = 1) in vec3 vNormal;
layout (location = 2) in vec2 vTexCoord;

//matrices de entrada
uniform mat4 projection;
uniform mat4 modelview;
uniform mat4 normalMat;

//variables de salida
varying vec3 normalInterp;
varying vec3 vertPos;

void main(){
    //pasamos a espacio de ojo
    vec4 vPos2 = vec4(vPos.x, vPos.y, 0.0, 1,0);
    gl_Position = projection * modelview * vec4(vPos, 1.0);
    vec4 vertPos4 = modelview * vec4(vPos, 1.0);
    vertPos = vec3(vertPos4) / vertPos4.w;
    texPos=vTexCoord;
    normalInterp = vec3(normalMat * vec4(vNormal, 0.0));
}
    
