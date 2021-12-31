#version 330 core

in vec4 pos;
in vec3 vertexColor;

uniform vec4 colour;
uniform vec2 light_pos;

out vec4 color;

void main()
{
  float intensity = 0.5 / length(pos.xy - light_pos);
  color = vec4(vertexColor, 1.0f) * intensity;
}
