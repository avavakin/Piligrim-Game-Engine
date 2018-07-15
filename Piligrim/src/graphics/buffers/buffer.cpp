#include "buffer.h"

piligrim::graphics::Buffer::Buffer(GLfloat * data, GLuint count, GLuint componentCount, GLint drawMode)
	:componentCount(componentCount)
{
	glGenBuffers(1, &bufferId);
	bind();
	glBufferData(GL_ARRAY_BUFFER, count * sizeof(GLfloat), data, drawMode);
	unbind();

}

void piligrim::graphics::Buffer::bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, bufferId);
}

void piligrim::graphics::Buffer::unbind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
