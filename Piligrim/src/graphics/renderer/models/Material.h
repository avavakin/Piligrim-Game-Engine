#pragma once
#include "Texture.h"
namespace piligrim {
	namespace graphics {
		struct Material
		{
		public:
			Texture diffuse;
			Texture specular;
			float shininess;
		};
	}
}