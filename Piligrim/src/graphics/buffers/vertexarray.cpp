#include "vertexarray.h"

piligrim::graphics::VertexArray::VertexArray()
{
	glGenVertexArrays(1, &arrayId);
	buffer_ = nullptr;
}

piligrim::graphics::VertexArray::~VertexArray()
{
	if (buffer_ != nullptr)
		delete[] buffer_;
}

void piligrim::graphics::VertexArray::setBuffer(Buffer* buffer)
{
	buffer_ = buffer;
}

void piligrim::graphics::VertexArray::addBufferAttributes(GLuint index, GLuint elementCount, GLsizei stride, GLuint leftPaddingInBytes)
{
	bind();
	buffer_->bind();

	glEnableVertexAttribArray(index);
	glVertexAttribPointer(index, elementCount, GL_FLOAT, GL_FALSE, stride, (GLvoid*)leftPaddingInBytes);
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
