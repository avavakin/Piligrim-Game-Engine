#version 330 core

out vec4 color;

uniform vec4 light_color = vec4(1.0);

void main()
{
	color = light_color;
}
