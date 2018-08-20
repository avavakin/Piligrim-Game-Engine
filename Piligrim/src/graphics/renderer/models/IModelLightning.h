#pragma once

#include "../shader/shader.h"

class IModelLightning
{
public:
	virtual void calcModelLightning(Shader* shader) = 0;
};