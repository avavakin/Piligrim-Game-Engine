#include "camera.h"
namespace piligrim {
	namespace graphics {



		Camera::Camera()
		{
			set(math::vec3(0, 0, 0), math::vec3(0, 0, -1));
		}



		Camera::Camera(math::vec3 position)
		{
			set(position, position + math::vec3(0.0, 0.0, 1.0));
		}



		Camera::Camera(math::vec3 position, math::vec3 lookPoint)
		{
			set(position, lookPoint);
		}



		void Camera::set(math::vec3 position, math::vec3 lookPoint)
		{
			_ASSERT(position != lookPoint);
			position_ = position;
			lookAt(lookPoint);
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