#include "buffer.h"
namespace piligrim {
	namespace graphics {



		Buffer::Buffer(GLvoid * data, GLuint size, GLint drawMode)
		{
			GLCall(glGenBuffers(1, &id_));
			GLCall(glBindBuffer(GL_ARRAY_BUFFER, id_));
			GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, drawMode));
			GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));

		}



		void Buffer::bind() const
		{
			GLCall(glBindBuffer(GL_ARRAY_BUFFER, id_));
		}



		void Buffer::unbind() const
		{
			GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
		}



	}
}
