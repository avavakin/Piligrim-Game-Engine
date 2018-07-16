#pragma once
#include <vector>
#include "isceneobject.h"
namespace piligrim {
	namespace graphics {

		class SceneGraph : public ISceneObject
		{
		private:
			std::vector<ISceneObject> objects;
		public:
			void applyMatrix(math::mat4 matr);
			void addObject(const ISceneObject &object);
			void clearScene();
			void draw();
		};

	}
}