#pragma once

#include <GL/glew.h>

namespace piligrim {
	namespace graphics {
		class IndexBuffer {
		private:
			GLuint bufferId;
			GLuint count;
		public:
			IndexBuffer(GLuint *data, GLuint count, GLint drawMode = GL_STATIC_DRAW);
			GLuint getCount() const { return count; }

			void bind() const;
			void unbind() const;


		};
	}
}