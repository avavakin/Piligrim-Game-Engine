#pragma once
#include <vector>
#include "sceneobject.h"
namespace piligrim {
	namespace graphics {

		class SceneGraph : SceneObject
		{
		private:
			std::vector<SceneObject> objects;
		public:
			void applyMatrix(math::mat4 matr);
		};

	}
}