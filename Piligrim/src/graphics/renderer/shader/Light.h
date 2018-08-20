#pragma once

#include "../../../math/vec3.h"

struct Light
{
	vec3 position;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};