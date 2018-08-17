#include "ModelState.h"



ModelState::ModelState()
	: needCalcTransMat_(true), needCalcRotateMat_(true), needCalcScaleMat_(true)
{
	rotateAxis_.x = 1.0f;
	rotateAngle_ = 0.0f;
	scaleVec_ = vec3(1.0f, 1.0f, 1.0f);
}



void ModelState::calcModelMatrix(Shader& shader)
{
	shader.setUniform("u_translation_matrix", calcTransMat());
	shader.setUniform("u_rotate_matrix",      calcRotateMat());
	shader.setUniform("u_scale_matrix",       calcScaleMat());
}



vec3 ModelState::getPosition() const
{
	return position_;
}



vec3 ModelState::getRotateAxis() const
{
	return rotateAxis_;
}



float ModelState::getRotateAngle() const
{
	return rotateAngle_;
}



vec3 ModelState::getScale() const
{
	return scaleVec_;
}



void ModelState::setPosition(const vec3 & position)
{
	if (position != position_) {
		position_ = position;
		needCalcTransMat_ = true;
	}
}



void ModelState::setRotateAxis(const vec3 & rotateAxis)
{
	if (rotateAxis != rotateAxis_) {
		rotateAxis_ = rotateAxis;
		needCalcRotateMat_ = true;
	}
}



void ModelState::setRotateAngle(float rotateAngle)
{
	if (rotateAngle != rotateAngle_) {
		rotateAngle_ = rotateAngle;
		needCalcRotateMat_ = true;
	}
}



void ModelState::setScale(const vec3 & scaleVec)
{
	if (scaleVec != scaleVec_) {
		scaleVec_ = scaleVec;
		needCalcScaleMat_ = true;
	}
}



void ModelState::setScaleX(float scaleX)
{
	if (scaleX != scaleVec_.x) {
		scaleVec_.x = scaleX;
		needCalcScaleMat_ = true;
	}
}



void ModelState::setScaleY(float scaleY)
{
	if (scaleY != scaleVec_.y) {
		scaleVec_.y = scaleY;
		needCalcScaleMat_ = true;
	}
}



void ModelState::setScaleZ(float scaleZ)
{
	if (scaleZ != scaleVec_.z) {
		scaleVec_.z = scaleZ;
		needCalcScaleMat_ = true;
	}
}



mat4 ModelState::calcTransMat()
{
	if (needCalcTransMat_) {
		transMat_ = mat4::translation(position_);
		needCalcTransMat_ = false;
	}
	return transMat_;
}



mat4 ModelState::calcRotateMat()
{
	if (needCalcRotateMat_) {
		rotateMat_ = mat4::rotation(rotateAxis_, rotateAngle_);
		needCalcRotateMat_ = false;
	}
	return rotateMat_;
}



mat4 ModelState::calcScaleMat()
{
	if (needCalcScaleMat_) {
		scaleMat_ = mat4::scale(scaleVec_);
		needCalcScaleMat_ = false;
	}
	return scaleMat_;
}
