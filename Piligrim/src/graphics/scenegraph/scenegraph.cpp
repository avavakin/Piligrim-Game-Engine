#include "scenegraph.h"

void piligrim::graphics::SceneGraph::applyMatrix(math::mat4 matr)
{
	for (auto& object : objects)
	{
		object.applyMatrix(matr);
	}
}
