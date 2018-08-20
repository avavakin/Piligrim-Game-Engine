#pragma once

#include "../../../math/math.h"
#include "../../../math/math_func.h"

#include "../../../controls/controllers/Controller.h"
#include "../../../controls/controllers/IControlsObserver.h"

class Camera : public IControlsObserver
{
public:
	Camera();
	Camera(vec3 position);
	Camera(vec3 position, vec3 lookPoint);
	void set(vec3 position, vec3 lookPoint);
	void setSpeed(float speed);
	void setSensitivity(float sensitivity);

	void setPosition(vec3 position);
	void setPosX(float x);
	void setPosY(float y);
	void setPosZ(float z);
	void setLookDir(vec3 lookDir);

	void setFov(float fov);
	void setNear(float near);
	void setFar(float far);
	void setRatio(float ratio);

	vec3 getPosition() const;
	vec3 getLookDir() const;
	vec3 getRightDir() const;

	mat4 calcLookAtMatrix();
	mat4 calcProjectionMatrix();

	void lookAt(vec3 lookPoint);
	void lookAt(float yaw, float pitch);

	void onControllerEvent(Controller* controller, double deltaTime);

private:
	vec3 position_;
	vec3 backDir_;
	vec3 rightDir_;
	vec3 upDir_;

	mat4 lookAtMatrix_;
	mat4 projectionMatrix_;

	float fovAngle_;
	float nearPlane_;
	float farPlane_;
	float ratio_;

	float yaw_;
	float pitch_;
	float sensitivity_;
	float speed_;

	bool needCalcMatrixPosition_ = true;
	bool needCalcMatrixDirection_ = true;
	bool needCalcMatrixProjection_ = true;

	ControlsTable* controlsTable_;

private:
	void calcMatrixPositionPart();
	void calcMatrixOtherPart();
	void calcMatrixAll();

};