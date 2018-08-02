#include "buffer.h"

piligrim::graphics::Buffer::Buffer(GLfloat * data, GLuint count, GLint drawMode)
{
	GLCall(glGenBuffers(1, &id_));
	bind();
	GLCall(glBufferData(GL_ARRAY_BUFFER, count * sizeof(GLfloat), data, drawMode));
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
