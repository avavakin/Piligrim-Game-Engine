#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoords;

uniform mat4 u_pr_matrix;
uniform mat4 u_vw_matrix = mat4(1.0);
uniform mat4 u_scale_matrix = mat4(1.0);
uniform mat4 u_rotate_matrix = mat4(1.0);
uniform mat4 u_translation_matrix = mat4(1.0);

out vec3 Normal;
out vec3 FragPos;
out vec2 TexCoords;

void main()
{
	mat4 ml_matrix = u_translation_matrix * u_rotate_matrix * u_scale_matrix;
	vec4 modelPoint = ml_matrix * vec4(position, 1.0);
	gl_Position = u_pr_matrix * u_vw_matrix * modelPoint;
	FragPos = vec3(modelPoint);
	Normal = mat3(transpose(inverse(ml_matrix))) * normal;
	TexCoords = texCoords;
}
