#pragma once
#include "Texture.h"

struct Material
{
public:
	Texture * diffuse;
	Texture* specular;
	float shininess;
};