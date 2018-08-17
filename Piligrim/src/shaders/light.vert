#version 330 core

layout (location = 0) in vec3 position;

uniform mat4 u_pr_matrix;
uniform mat4 u_vw_matrix = mat4(1.0);
uniform mat4 u_scale_matrix = mat4(1.0);
uniform mat4 u_rotate_matrix = mat4(1.0);
uniform mat4 u_translation_matrix = mat4(1.0);

void main()
{
	mat4 ml_matrix = u_translation_matrix * u_rotate_matrix * u_scale_matrix;
	gl_Position = u_pr_matrix * u_vw_matrix * ml_matrix * vec4(position, 1.0);
}
