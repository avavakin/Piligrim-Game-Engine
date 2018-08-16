#pragma once

#include <GL/glew.h>

#include "../../utils/glcall.h"

class Buffer {
public:
	Buffer(GLvoid *data, GLuint size, GLenum drawMode = GL_STATIC_DRAW);

	void bind() const;
	void unbind() const;

private:
	GLuint id_;
};