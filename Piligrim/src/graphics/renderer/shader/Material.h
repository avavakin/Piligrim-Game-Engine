#pragma once
#include "../meshes/Texture.h"

struct Material
{
public:
	Texture* diffuse;
	Texture* specular;
	float shininess;
};