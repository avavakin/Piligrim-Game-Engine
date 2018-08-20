#include "SolidLightning.h"



SolidLightning::SolidLightning(Light * light, Camera * camera)
{
	light_ = light;
	camera_ = camera;
}



void SolidLightning::calcModelLightning(Shader * shader)
{
	shader->setUniform("u_light.position", light_->position);
	shader->setUniform("u_cam_pos", camera_->getPosition());
}

void SolidLightning::setLight(Light * light)
{
	light_ = light;
}

void SolidLightning::setCamera(Camera * camera)
{
	camera_ = camera;
}
