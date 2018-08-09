#pragma once

#include <GL/glew.h>

#include "../../utils/glcall.h"

namespace piligrim {
	namespace graphics {

		class Buffer {
		public:
			Buffer(GLvoid *data, GLuint size, GLint drawMode = GL_STATIC_DRAW);

			void bind() const;
			void unbind() const;

		private:
			GLuint id_;
		};

	}
}