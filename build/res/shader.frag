#version 330

in vec3 vertexOutColour;
out vec3 color;

void main(){
  color = vertexOutColour;
}