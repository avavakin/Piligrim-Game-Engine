#version 330 core

out vec4 color;

in vec3 FragPos;
in vec3 Normal;


uniform vec3 u_light_pos;
uniform vec3 u_cam_pos;

uniform vec3 u_object_color;
uniform vec3 u_light_color;

void main()
{
	float ambientStrength = 0.1f;
	vec3 ambient = ambientStrength * u_light_color;
	
	vec3 norm = normalize(Normal);

	vec3 lightDir = normalize(u_light_pos - FragPos);
	float diff = max(dot(norm, lightDir), 0.0f);
	vec3 diffuse = diff * u_light_color;

	float specularStrength = 0.5f;
	vec3 camDir = normalize(u_cam_pos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(  max( dot(camDir, reflectDir), 0.0f ) , 32); 
	vec3 specular = specularStrength * spec * u_light_color;

	color = vec4( (ambient + diff) * u_object_color , 1.0f);
}
