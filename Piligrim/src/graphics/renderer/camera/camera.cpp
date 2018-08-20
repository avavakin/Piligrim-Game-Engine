#include "camera.h"



Camera::Camera()
	: speed_(100.0f), sensitivity_(0.9f), yaw_(-90.0f), pitch_(0.0f)
{
	set(vec3(0.0f), - vec3::oz());
}



Camera::Camera(vec3 position)
	: speed_(100.0f), sensitivity_(0.9f), yaw_(-90.0f), pitch_(0.0f)
{
	set(position, position + vec3::oz());
}



Camera::Camera(vec3 position, vec3 lookPoint)
	: speed_(100.0f), sensitivity_(0.9f), yaw_(-90.0f), pitch_(0.0f)
{
	set(position, lookPoint);
}



void Camera::set(vec3 position, vec3 lookPoint)
{
	_ASSERT(position != lookPoint);
	position_ = position;
	lookAt(lookPoint);
}



void Camera::setSpeed(float speed)
{
	speed_ = speed;
}



void Camera::setSensitivity(float sensitivity)
{
	sensitivity_ = sensitivity;
}



void Camera::setPosition(vec3 position)
{
	position_ = position;
	needCalcMatrixPosition_ = true;
}



vec3 Camera::getPosition() const
{
	return position_;
}



void Camera::setPosX(float x)
{
	position_.x = x;
	needCalcMatrixPosition_ = true;
}



void Camera::setPosY(float y)
{
	position_.y = y;
	needCalcMatrixPosition_ = true;
}



void Camera::setPosZ(float z)
{
	position_.z = z;
	needCalcMatrixPosition_ = true;
}



void Camera::lookAt(vec3 lookPoint)
{
	setLookDir(lookPoint - position_);
}



void Camera::lookAt(float yaw, float pitch)
{
	vec3 newCamDir;

	if (pitch_ > 90.0f) {
		pitch_ = 90.0f;
	}
	else if (pitch_ < -80.0f) {
		pitch_ = -80.0f;
	}

	if (yaw_ > 360.0f) {
		yaw -= 360.0f;
	}

	if (yaw_ < -360.0f) {
		yaw += 360.0f;
	}

	newCamDir = vec3(
		cos(toRadians(pitch_)) * cos(toRadians(yaw_)),
		sin(toRadians(pitch_)),
		cos(toRadians(pitch_)) * sin(toRadians(yaw_))
	);

	setLookDir(newCamDir);
}



void Camera::onControllerEvent(Controller* controller, double deltaTime)
{
	bool needMoveForward = controller->isKeyActive(KeyRole::Forward);
	bool needMoveBack = controller->isKeyActive(KeyRole::Back);
	bool needMoveLeft = controller->isKeyActive(KeyRole::Left);
	bool needMoveRight = controller->isKeyActive(KeyRole::Right);
	bool needMoveDown = controller->isKeyActive(KeyRole::Down);
	bool needMoveUp = controller->isKeyActive(KeyRole::Up);
	bool needLookAtCenter = controller->isKeyActive(KeyRole::Center);

	if (needMoveForward) {
		setPosition(position_ - backDir_ * speed_ * deltaTime);
	}

	if (needMoveBack) {
		setPosition(position_ + backDir_ * speed_ * deltaTime);
	}

	if (needMoveLeft) {
		setPosition(position_ - rightDir_ * speed_ * deltaTime);
	}

	if (needMoveRight) {
		setPosition(position_ + rightDir_ * speed_ * deltaTime);
	}

	if (needMoveDown) {
		setPosition(position_ - vec3::oy() * speed_ * deltaTime);
	}

	if (needMoveUp) {
		setPosition(position_ + vec3::oy() * speed_ * deltaTime);
	}

	if (needLookAtCenter) {
		lookAt(vec3(0.0f));
	}
	else {
		vec2 offset = controller->getMouseDelta();
		offset *= sensitivity_;

		yaw_ += offset.x;
		pitch_ += offset.y;

		lookAt(yaw_, pitch_);
	}
}



void Camera::setLookDir(vec3 lookDir)
{
	if (lookDir == -backDir_) {
		return;
	}

	backDir_ = -lookDir;
	backDir_ = backDir_.getNormalize();
	rightDir_ = vec3::oy().crossProduct(backDir_).getNormalize();
	upDir_ = backDir_.crossProduct(rightDir_);

	needCalcMatrixDirection_ = true;
}



void Camera::setFov(float fov)
{
	fovAngle_ = fov;
	needCalcMatrixProjection_ = true;
}



void Camera::setNear(float near)
{
	nearPlane_ = near;
	needCalcMatrixProjection_ = true;
}



void Camera::setFar(float far)
{
	farPlane_ = far;
	needCalcMatrixProjection_ = true;
}



void Camera::setRatio(float ratio)
{
	ratio_ = ratio;
	needCalcMatrixProjection_ = true;
}



vec3 Camera::getLookDir() const
{
	return -backDir_;
}



vec3 Camera::getRightDir() const
{
	return rightDir_;
}



mat4 Camera::calcLookAtMatrix()
{
	if (needCalcMatrixDirection_) {
		calcMatrixAll();
		needCalcMatrixPosition_ = false;
		needCalcMatrixDirection_ = false;
	}
	else if (needCalcMatrixPosition_) {
		calcMatrixPositionPart();
		needCalcMatrixPosition_ = false;
	}

	return lookAtMatrix_;
}



mat4 Camera::calcProjectionMatrix()
{
	if (needCalcMatrixProjection_) {
		projectionMatrix_ = mat4::perspective(fovAngle_, ratio_, nearPlane_, farPlane_);
		needCalcMatrixProjection_ = false;
	}
	return projectionMatrix_;
}



void Camera::calcMatrixPositionPart()
{
	vec3 negPosition = -position_;
	lookAtMatrix_.columns[3].x = negPosition.scalProduct(rightDir_);
	lookAtMatrix_.columns[3].y = negPosition.scalProduct(upDir_);
	lookAtMatrix_.columns[3].z = negPosition.scalProduct(backDir_);
}



void Camera::calcMatrixOtherPart()
{
	lookAtMatrix_.columns[0].x = rightDir_.x;
	lookAtMatrix_.columns[0].y = upDir_.x;
	lookAtMatrix_.columns[0].z = backDir_.x;
	lookAtMatrix_.columns[0].w = 0;

	lookAtMatrix_.columns[1].x = rightDir_.y;
	lookAtMatrix_.columns[1].y = upDir_.y;
	lookAtMatrix_.columns[1].z = backDir_.y;
	lookAtMatrix_.columns[1].w = 0;

	lookAtMatrix_.columns[2].x = rightDir_.z;
	lookAtMatrix_.columns[2].y = upDir_.z;
	lookAtMatrix_.columns[2].z = backDir_.z;
	lookAtMatrix_.columns[2].w = 0;
}



void Camera::calcMatrixAll()
{
	calcMatrixOtherPart();
	calcMatrixPositionPart();
	lookAtMatrix_.columns[3].w = 1;
}