#pragma once

#include <GL/glew.h>

namespace piligrim {
	namespace graphics {
		class Buffer {
		private:
			GLuint bufferId;
		public:
			Buffer(GLfloat *data, GLuint count, GLint drawMode = GL_STATIC_DRAW);

			void bind() const;
			void unbind() const;


		};
	}
}