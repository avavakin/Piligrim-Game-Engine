#pragma once

#include <GL/glew.h>

namespace piligrim {
	namespace graphics {
		class Buffer {
		private:
			GLuint bufferId;
			GLuint componentCount;
		public:
			Buffer(GLfloat *data, GLuint count, GLuint componentCount, GLint drawMode = GL_STATIC_DRAW);
			GLuint getComponentCount() const { return componentCount; }

			void bind() const;
			void unbind() const;


		};
	}
}