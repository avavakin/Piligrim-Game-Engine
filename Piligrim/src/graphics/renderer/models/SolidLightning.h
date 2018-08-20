#pragma once

#include "../shader/Light.h"
#include "../camera/camera.h"

#include "IModelLightning.h"

class SolidLightning : public IModelLightning
{
public:
	SolidLightning(Light* light, Camera* camera);

	void calcModelLightning(Shader* shader);
	void setLight(Light* light);
	void setCamera(Camera* camera);

private:
	Light* light_;
	Camera* camera_;
};