#pragma once

#include "../../../math/math.h"

#include "../../shader.h"

class ModelState
{
public:
	ModelState();

	void calcModelMatrix(Shader& shader);

	vec3 getPosition() const;
	vec3 getRotateAxis() const;
	float getRotateAngle() const;
	vec3 getScale() const;

	void setPosition(const vec3& position);
	void setRotateAxis(const vec3& rotateAxis);
	void setRotateAngle(float rotateAngle);

	void setScale(const vec3& scaleVec);
	void setScaleX(float scaleX);
	void setScaleY(float scaleY);
	void setScaleZ(float scaleZ);

private:
	vec3 position_;
	vec3 rotateAxis_;
	float rotateAngle_;
	vec3 scaleVec_;

	mat4 transMat_;
	mat4 rotateMat_;
	mat4 scaleMat_;

	bool needCalcTransMat_;
	bool needCalcRotateMat_;
	bool needCalcScaleMat_;

private:
	mat4 calcTransMat();
	mat4 calcRotateMat();
	mat4 calcScaleMat();
};