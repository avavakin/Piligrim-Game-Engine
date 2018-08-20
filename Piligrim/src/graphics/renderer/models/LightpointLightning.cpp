#include "LightpointLightning.h"



LightpointLightning::LightpointLightning(const vec3& color, float opacity)
{
	color_ = vec4(color, opacity);
}



void LightpointLightning::calcModelLightning(Shader * shader)
{
	shader->setUniform("light_color", color_);
}



void LightpointLightning::setColor(const vec3 & color)
{
	color_.x = color.x;
	color_.y = color.y;
	color_.z = color.z;
}



void LightpointLightning::setOpacity(float opacity)
{
	color_.w = opacity;
}
