#include "camera.h"

piligrim::graphics::Camera::Camera()
{
	set(math::vec3(0,0,0), math::vec3(0,0,-1));
}

piligrim::graphics::Camera::Camera(math::vec3 position)
{
	set(position, position + math::vec3(0.0, 0.0, 1.0));
}

piligrim::graphics::Camera::Camera(math::vec3 position, math::vec3 lookPoint)
{
	set(position, lookPoint);
}
