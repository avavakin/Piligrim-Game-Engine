#include "camera.h"
namespace piligrim {
	namespace graphics {



		Camera::Camera()
			: speed_(100.0f), sensitivity_(0.9f), yaw_(-90.0f), pitch_(0.0f)
		{
			set(math::vec3(0, 0, 0), math::vec3(0, 0, -1));
		}



		Camera::Camera(math::vec3 position)
			: speed_(100.0f), sensitivity_(0.9f), yaw_(-90.0f), pitch_(0.0f)
		{
			set(position, position + math::vec3(0.0, 0.0, 1.0));
		}



		Camera::Camera(math::vec3 position, math::vec3 lookPoint)
			: speed_(100.0f), sensitivity_(0.9f), yaw_(-90.0f), pitch_(0.0f)
		{
			set(position, lookPoint);
		}



		void Camera::set(math::vec3 position, math::vec3 lookPoint)
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



		void Camera::setPosition(math::vec3 position)
		{
			position_ = position;
			isMatrixPositionOld_ = true;
		}



		math::vec3 Camera::getPosition() const
		{
			return position_;
		}



		void Camera::setPosX(float x)
		{
			position_.x = x;
			isMatrixPositionOld_ = true;
		}



		void Camera::setPosY(float y)
		{
			position_.y = y;
			isMatrixPositionOld_ = true;
		}



		void Camera::setPosZ(float z)
		{
			position_.z = z;
			isMatrixPositionOld_ = true;
		}



		void Camera::lookAt(math::vec3 lookPoint)
		{
			setLookDir(lookPoint - position_);
		}

		void Camera::lookAt(float yaw, float pitch)
		{
			math::vec3 newCamDir;

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

			newCamDir = math::vec3(
				cos(math::toRadians(pitch_)) * cos(math::toRadians(yaw_)),
				sin(math::toRadians(pitch_)),
				cos(math::toRadians(pitch_)) * sin(math::toRadians(yaw_))
			);

			setLookDir(newCamDir);
		}

		void Camera::onControllerEvent(Controller* controller, double deltaTime)
		{
			bool needMoveForward  = controller->isKeyActive(KeyRole::Forward);
			bool needMoveBack     = controller->isKeyActive(KeyRole::Back);
			bool needMoveLeft     = controller->isKeyActive(KeyRole::Left);
			bool needMoveRight    = controller->isKeyActive(KeyRole::Right);
			bool needMoveDown     = controller->isKeyActive(KeyRole::Down);
			bool needMoveUp       = controller->isKeyActive(KeyRole::Up);
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
				setPosition(position_ - math::vec3(0.0f, 1.0f, 0.0f) * speed_ * deltaTime);
			}

			if (needMoveUp) {
				setPosition(position_ + math::vec3(0.0f, 1.0f, 0.0f) * speed_ * deltaTime);
			}

			if (needLookAtCenter) {
				lookAt(math::vec3(0.0f, 0.0f, 0.0f));
			}
			else {
				math::vec2 offset = controller->getMouseDelta();
				offset *= sensitivity_;

				yaw_ += offset.x;
				pitch_ += offset.y;
				
				lookAt(yaw_, pitch_);
			}
		}



		void Camera::setLookDir(math::vec3 lookDir)
		{
			if (lookDir == -backDir_) {
				return;
			}

			backDir_ = -lookDir;
			backDir_ = backDir_.getNormalize();
			rightDir_ = math::vec3(0, 1, 0).crossProduct(backDir_).getNormalize();
			upDir_ = backDir_.crossProduct(rightDir_);

			isMatrixDirectionOld_ = true;
		}



		math::vec3 Camera::getLookDir() const
		{
			return -backDir_;
		}



		math::vec3 Camera::getRightDir() const
		{
			return rightDir_;
		}



		math::mat4 Camera::getMatrix()
		{
			if (isMatrixDirectionOld_) {
				calcMatrixAll();
				isMatrixPositionOld_ = false;
				isMatrixDirectionOld_ = false;
			}
			else if (isMatrixPositionOld_) {
				calcMatrixPositionPart();
				isMatrixPositionOld_ = false;
			}

			return lookAtMatrix_;
		}



		void Camera::calcMatrixPositionPart()
		{
			math::vec3 negPosition = -position_;
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



	}
}