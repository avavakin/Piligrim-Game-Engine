#pragma once

#include "../../../math/vec3.h"
#include "../../../math/vec4.h"

#include "IModelLightning.h"

class LightpointLightning : public IModelLightning
{
public:
	LightpointLightning(const vec3& color = vec3(1.0f), float opacity = 1.0f);

	void calcModelLightning(Shader* shader);

	void setColor(const vec3& color);
	void setOpacity(float opacity);

private:
	vec4 color_;
};