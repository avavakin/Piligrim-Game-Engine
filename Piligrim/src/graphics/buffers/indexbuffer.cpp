#include "indexbuffer.h"

piligrim::graphics::IndexBuffer::IndexBuffer(GLuint *data, GLuint count, GLint drawMode)
	:count_(count)
{
	GLCall(glGenBuffers(1, &id_));
	bind();
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GLuint), data, drawMode));
	unbind();
}

void piligrim::graphics::IndexBuffer::bind() const
{
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_));
}

void piligrim::graphics::IndexBuffer::unbind() const
{
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}
