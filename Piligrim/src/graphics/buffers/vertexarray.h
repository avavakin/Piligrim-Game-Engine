#pragma once

#include <vector>

#include <GL/glew.h>

#include "../../utils/glcall.h"
#include "buffer.h"

namespace piligrim {
	namespace graphics {

		class VertexArray {
		public:
			VertexArray();
			~VertexArray();

			void setBuffer(Buffer* buffer);

			void addBufferAttributes(GLuint index, GLuint elementCount, GLsizei stride, GLuint leftPaddingInBytes);

			void bind() const;
			void unbind() const;

		private:
			GLuint id_;
			Buffer* buffer_;
		};

	}
}