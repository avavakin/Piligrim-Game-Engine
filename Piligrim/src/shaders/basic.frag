#version 330 core

out vec4 color;

uniform vec4 u_color;
uniform vec2 u_light_pos;


in DATA
{
	vec4 pos;
	vec4 color;
} fs_in;

void main()
{
	float intensivity = 1 / (10*length(fs_in.pos.xy-u_light_pos));
	color = fs_in.color * intensivity;
}
