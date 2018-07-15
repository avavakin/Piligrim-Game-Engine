#include "indexbuffer.h"

piligrim::graphics::IndexBuffer::IndexBuffer(GLuint *data, GLuint count, GLint drawMode)
	:count(count)
{
	glGenBuffers(1, &bufferId);
	bind();
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GLuint), data, drawMode);
	unbind();
}

void piligrim::graphics::IndexBuffer::bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferId);
}

void piligrim::graphics::IndexBuffer::unbind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
