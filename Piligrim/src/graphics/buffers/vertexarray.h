#pragma once

#include <GL/glew.h>
#include <vector>
#include "buffer.h"

namespace piligrim {
	namespace graphics {
		class VertexArray {
		private:
			GLuint arrayId;
			Buffer* buffer_;
		public:
			VertexArray();
			~VertexArray();

			void setBuffer(Buffer* buffer);

			void addBufferAttributes(GLuint index, GLuint elementCount, GLsizei stride, GLuint leftPaddingInBytes);

			void bind() const;
			void unbind() const;


		};
	}
}