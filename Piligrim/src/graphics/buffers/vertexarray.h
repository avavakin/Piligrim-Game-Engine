#pragma once

#include <vector>

#include <GL/glew.h>

#include "../../utils/glcall.h"
#include "buffer.h"

class VertexArray {
public:
	VertexArray();

	void setBuffer(Buffer* buffer);

	void addBufferAttributes(GLuint index, GLuint elementCount, GLsizei stride, GLuint leftPaddingInBytes);

	void bind() const;
	void unbind() const;

	void deleteBuffer() const;

private:
	GLuint id_;
	Buffer* buffer_;
};