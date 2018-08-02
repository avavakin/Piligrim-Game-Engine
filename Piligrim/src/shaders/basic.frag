#version 330 core

out vec4 color;

struct Material 
{
	sampler2D diffuse;
	sampler2D specular;
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
in vec2 TexCoords;

uniform vec3 u_cam_pos;
uniform sampler2D tet;

uniform Material u_material;
uniform Light u_light;

vec3 calcColor(Material material, Light light)
{
	vec3 norm = normalize(Normal);

	vec3 lightDir = normalize(light.position - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	vec3 camDir = normalize(u_cam_pos - FragPos);

	float diff = max(
		dot(norm, lightDir), 
		0.0f
	);

	float spec = pow(
		max(
			dot(camDir, reflectDir), 
			0.0f
		), 
		material.shininess
	); 

	vec3 materialDiffuse = vec3(texture(material.diffuse, TexCoords));
	vec3 materialSpecular = vec3(texture(material.specular, TexCoords));

	vec3 ambient  = light.ambient * materialDiffuse;
	vec3 diffuse  = light.diffuse * materialDiffuse * diff;
	vec3 specular = light.specular * materialSpecular * spec;

	return ambient + diffuse + specular;
}

void main()
{
	color = vec4(calcColor(u_material, u_light), 1.0f);
}
