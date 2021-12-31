#version 330 core

layout (location = 0) in vec4 inPosition;
layout (location = 1) in vec3 inColor;

uniform mat4 pr_matrix;
uniform mat4 vw_matrix = mat4(1.0);
uniform mat4 ml_matrix = mat4(1.0);

out vec4 pos;
out vec3 vertexColor;

void main()
{
  gl_Position = pr_matrix * vw_matrix * ml_matrix * inPosition;
  pos = ml_matrix * inPosition;
  vertexColor = inColor;
}
