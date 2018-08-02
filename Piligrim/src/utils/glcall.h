#pragma once
#include <iostream>
#include <string>
#include <GL/glew.h>

#define DEBUG

#ifndef ASSERT
#define ASSERT(x) if (!(x)) __debugbreak();
#endif

inline void GLClearError()
{
	while (glGetError() != GL_NO_ERROR);
}

inline bool GLLogCall(std::string function, unsigned int line, std::string fileName)
{
	if (GLenum error = glGetError()) {
		std::cerr << "[OpenGL ERROR] | " << error << " | ";

		switch (error) {
		case GL_INVALID_ENUM : 
			std::cerr << "Invalid Enum";
			break;
		case GL_INVALID_VALUE :
			std::cerr << "Invalid Value";
			break;
		case GL_INVALID_OPERATION :
			std::cerr << "Invalid Operation";
			break;
		case GL_STACK_OVERFLOW :
			std::cerr << "Stack Overflow";
			break;
		case GL_STACK_UNDERFLOW :
			std::cerr << "Stack Underflow";
			break;
		case GL_OUT_OF_MEMORY :
			std::cerr << "Out of memory";
			break;
		case GL_INVALID_FRAMEBUFFER_OPERATION :
			std::cerr << "Invalid FrameBuffer Operation";
			break;
		case GL_CONTEXT_LOST :
			std::cerr << "Context Lost";
			break;
		case GL_TABLE_TOO_LARGE :
			std::cerr << "Table too large";
			break;
		default :
			std::cerr << "Undefined error";
		}
		std::cerr << " | " << fileName << " | " << line << std::endl;
		return false;
	}
	return true;
}

#ifdef DEBUG 
#define GLCall(x) GLClearError(); \
x; \
ASSERT(GLLogCall(#x, __LINE__, __FILE__))
#else
#define GLCall(x) x;
#endif