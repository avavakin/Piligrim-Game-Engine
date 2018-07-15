#include "vertexarray.h"

piligrim::graphics::VertexArray::VertexArray()
{
	glGenVertexArrays(1, &arrayId);
}

piligrim::graphics::VertexArray::~VertexArray()
{
	for (unsigned int i = 0; i < buffers.size(); i++)
		delete buffers[i];
}

void piligrim::graphics::VertexArray::addBuffer(Buffer * buffer, GLuint index)
{
	bind();
	buffer->bind();

	glEnableVertexAttribArray(index);
	glVertexAttribPointer(index, buffer->getComponentCount(), GL_FLOAT, GL_FALSE, 0, 0);

	buffer->unbind();
	unbind();
}

void piligrim::graphics::VertexArray::bind() const
{
	glBindVertexArray(arrayId);
}

void piligrim::graphics::VertexArray::unbind() const
{
	glBindVertexArray(0);
}
