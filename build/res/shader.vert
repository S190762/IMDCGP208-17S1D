#version 330

layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec3 vertexColour;

uniform mat4 projViewMatrix;
uniform mat4 modelMatrix;

out vec3 vertexOutColour;

void main() {
  gl_Position = projViewMatrix * modelMatrix * vec4(vertexPosition, 1.0);
  vertexOutColour = vertexColour;
}