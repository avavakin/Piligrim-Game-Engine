#pragma once

#include <GL/glew.h>

#include "../../utils/glcall.h"

class IndexBuffer {
public:
	IndexBuffer() {};
	IndexBuffer(GLuint *data, GLuint count, GLenum drawMode = GL_STATIC_DRAW);

	void set(GLuint *data, GLuint count, GLenum drawMode = GL_STATIC_DRAW);

	GLuint getCount() const { return count_; }

	void bind() const;
	void unbind() const;

private:
	GLuint id_;
	GLuint count_;
};