#pragma once

namespace piligrim {
	namespace graphics {

		class Shader;

		class IDrawable
		{
		public:
			virtual void draw(Shader&) = 0;
		};

	}
}