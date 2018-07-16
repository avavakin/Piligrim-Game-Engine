#pragma once
#include "../../math/mat4.h"
namespace piligrim {
	namespace graphics {
		class SceneObject 
		{
		public:
			virtual void applyMatrix(math::mat4 matr) = 0;

		};
	}
}