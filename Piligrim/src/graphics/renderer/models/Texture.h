#pragma once
#include <string>

#include <GL/glew.h>

#include <FreeImage.h>
#include "../../../utils/imageload.h"
#include "../../../utils/glcall.h"

namespace piligrim {
	namespace graphics {

		class Texture
		{
		public:
			Texture(std::string fileName);
			~Texture();

			void bind(unsigned int slot = 0) const;
			void unbind() const;

		private:
			std::string fileName_;
			GLuint id_;
			unsigned int width_;
			unsigned int height_;
			BYTE* pixels_;
		private:
			GLuint load();
		};

	}
}