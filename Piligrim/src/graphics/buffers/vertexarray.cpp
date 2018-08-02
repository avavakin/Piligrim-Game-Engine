#include "vertexarray.h"

piligrim::graphics::VertexArray::VertexArray()
{
	GLCall(glGenVertexArrays(1, &id_));
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

	GLCall(glEnableVertexAttribArray(index));
	GLCall(glVertexAttribPointer(index, elementCount, GL_FLOAT, GL_FALSE, stride, (GLvoid*)leftPaddingInBytes));
	unbind();
}

void piligrim::graphics::VertexArray::bind() const
{
	GLCall(glBindVertexArray(id_));
}

void piligrim::graphics::VertexArray::unbind() const
{
	GLCall(glBindVertexArray(0));
}
