#include "buffer.h"

piligrim::graphics::Buffer::Buffer(GLvoid * data, GLuint size, GLint drawMode)
{
	GLCall(glGenBuffers(1, &id_));
	bind();
	GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, drawMode));
	unbind();

}

void piligrim::graphics::Buffer::bind() const
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, id_));
}

void piligrim::graphics::Buffer::unbind() const
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}
