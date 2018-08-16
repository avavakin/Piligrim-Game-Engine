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

	vec3 getPosition() const;
	vec3 getLookDir() const;
	vec3 getRightDir() const;

	mat4 getMatrix();
	void lookAt(vec3 lookPoint);
	void lookAt(float yaw, float pitch);

	void onControllerEvent(Controller* controller, double deltaTime);

private:
	vec3 position_;
	vec3 backDir_;
	vec3 rightDir_;
	vec3 upDir_;
	mat4 lookAtMatrix_;

	float yaw_;
	float pitch_;
	float sensitivity_;
	float speed_;

	bool isMatrixPositionOld_ = true;
	bool isMatrixDirectionOld_ = true;

	ControlsTable* controlsTable_;

private:
	void calcMatrixPositionPart();
	void calcMatrixOtherPart();
	void calcMatrixAll();

};