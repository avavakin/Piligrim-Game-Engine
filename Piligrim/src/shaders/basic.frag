#version 330 core

out vec4 color;

struct Material 
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};

struct Light {
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

in vec3 FragPos;
in vec3 Normal;

uniform vec3 u_cam_pos;

uniform Material u_material;
uniform Light u_light;

vec3 calcColor(Material material, Light light)
{
	vec3 ambient = material.ambient * light.ambient;
	
	vec3 norm = normalize(Normal);

	vec3 lightDir = normalize(light.position - FragPos);
	float diff = max(
		dot(norm, lightDir), 
		0.0f
	);
	vec3 diffuse = material.diffuse * light.diffuse * diff;

	vec3 camDir = normalize(u_cam_pos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(
		max(
			dot(camDir, reflectDir), 
			0.0f
		), 
		material.shininess
	); 
	vec3 specular = material.specular * light.specular * spec;

	return ambient + diffuse + specular;
}

void main()
{
	color = vec4(calcColor(u_material, u_light), 1.0f);
}
