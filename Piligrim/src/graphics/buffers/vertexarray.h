#pragma once

#include <GL/glew.h>
#include <vector>
#include "buffer.h"

namespace piligrim {
	namespace graphics {
		class VertexArray {
		private:
			GLuint arrayId;
			std::vector<Buffer*> buffers;
		public:
			VertexArray();
			~VertexArray();
			
			void addBuffer(Buffer *buffer, GLuint index);

			void bind() const;
			void unbind() const;


		};
	}
}