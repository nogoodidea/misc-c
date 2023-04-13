#version 330 core
layout (location = 0) in vec3 aPos;
// x,y,z cords
layout (location = 1) in vec3 aColor;
//r,g,b 

out vec3 color;

void main(){
  gl_Postition = vec4(aPos,1.0); // x,y,z + 1.0 alpha?
  ourColor = aColor; // color
}
