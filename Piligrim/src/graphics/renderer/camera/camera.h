#pragma once

#include "../../../math/math.h"

namespace piligrim 
{
	namespace graphics 
	{
		class Camera
		{
		public:
			Camera();
			Camera(math::vec3 position);
			Camera(math::vec3 position, math::vec3 lookPoint);
			void set(math::vec3 position, math::vec3 lookPoint);

			void setPosition(math::vec3 position);
			void setPosX(float x);
			void setPosY(float y);
			void setPosZ(float z);			
			void setLookDir(math::vec3 lookDir);
			
			math::vec3 getPosition() const;
			math::vec3 getLookDir() const;
			math::vec3 getRightDir() const;
			
			math::mat4 getMatrix();
			void lookAt(math::vec3 lookPoint);

		private:
			math::vec3 position_;
			math::vec3 backDir_;
			math::vec3 rightDir_;
			math::vec3 upDir_;
			math::mat4 lookAtMatrix_;
			bool isMatrixPositionOld_ = true;
			bool isMatrixDirectionOld_ = true;

		private:
			void calcMatrixPositionPart();
			void calcMatrixOtherPart();
			void calcMatrixAll();
			
		};
	}
}