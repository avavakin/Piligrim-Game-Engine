#pragma once
#include "../../../math/math.h"
namespace piligrim 
{
	namespace graphics 
	{
		class Camera
		{
		private:
			math::vec3 position_;
			math::vec3 backDir_;
			math::vec3 rightDir_;
			math::vec3 upDir_;
			math::mat4 lookAtMatrix_;
			bool isMatrixPositionOld_ = true;
			bool isMatrixDirectionOld_ = true;
		public:
			Camera();
			Camera(math::vec3 position);
			Camera(math::vec3 position, math::vec3 lookPoint);
			inline void set(math::vec3 position, math::vec3 lookPoint)
			{
				_ASSERT(position != lookPoint);
				position_ = position;
				lookAt(lookPoint);
			}

			inline void setPosition(math::vec3 position)
			{
				position_ = position;
				isMatrixPositionOld_ = true;
			}
			inline math::vec3 getPosition() const
			{
				return position_;
			}

			inline void setPosX(float x)
			{
				position_.x = x;
				isMatrixPositionOld_ = true;
			}
			inline void setPosY(float y)
			{
				position_.y = y;
				isMatrixPositionOld_ = true;
			}
			inline void setPosZ(float z)
			{
				position_.z = z;
				isMatrixPositionOld_ = true;
			}

			inline void lookAt(math::vec3 lookPoint)
			{
				setLookDir(lookPoint-position_);
			}

			inline void setLookDir(math::vec3 lookDir)
			{
				backDir_ = -lookDir;
				backDir_ = backDir_.getNormalize();
				rightDir_ = math::vec3(0, 1, 0).crossProduct(backDir_).getNormalize();
				upDir_ = backDir_.crossProduct(rightDir_);

				isMatrixDirectionOld_ = true;
			}
			inline math::vec3 getLookDir() const
			{
				return -backDir_;
			}

			inline math::mat4 getMatrix()
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
		private:
			inline void calcMatrixPositionPart()
			{
				lookAtMatrix_.columns[3].x = (-position_) * rightDir_;
				lookAtMatrix_.columns[3].y = (-position_) * upDir_;
				lookAtMatrix_.columns[3].z = (-position_) * backDir_;
			}
			inline void calcMatrixOtherPart()
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
			inline void calcMatrixAll()
			{
				calcMatrixOtherPart();
				calcMatrixPositionPart();
				lookAtMatrix_.columns[3].w = 1;
			}
		};
	}
}