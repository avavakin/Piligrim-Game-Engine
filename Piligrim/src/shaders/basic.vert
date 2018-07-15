#version 330 core

layout (location = 0) in vec4 position;
/*layout (location = 1) in vec4 in_color;*/

uniform mat4 u_pr_matrix;
uniform mat4 u_vw_matrix = mat4(1.0);
uniform mat4 u_ml_matrix = mat4(1.0);

out DATA
{
	vec4 pos;
	vec4 color;
} vs_out;

void main()
{
	vs_out.pos = u_ml_matrix * position;
	gl_Position = u_pr_matrix * u_vw_matrix * vs_out.pos;
	vs_out.color = vec4(0.0, 1.0, 0.0, 1.0);
}
