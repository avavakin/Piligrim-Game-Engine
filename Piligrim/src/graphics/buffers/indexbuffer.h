#pragma once

#include <GL/glew.h>

#include "../../utils/glcall.h"

namespace piligrim {
	namespace graphics {
		class IndexBuffer {
		public:
			IndexBuffer(GLuint *data, GLuint count, GLint drawMode = GL_STATIC_DRAW);
			GLuint getCount() const { return count_; }

			void bind() const;
			void unbind() const;

		private:
			GLuint id_;
			GLuint count_;
		};
	}
}