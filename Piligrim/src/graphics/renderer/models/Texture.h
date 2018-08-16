#pragma once
#include <string>

#include <GL/glew.h>

#include <FreeImage.h>
#include "../../../utils/imageload.h"
#include "../../../utils/glcall.h"

class Texture
{
public:
	Texture(std::string fileName, unsigned int slot = 0);
	~Texture();

	void bind() const;
	void unbind() const;

	GLuint getId() const;
	unsigned int getWidth() const;
	unsigned int getHeight() const;
	unsigned int getSlot() const;

	void setSlot(unsigned int slot);

	void load(std::string fileName);

private:
	unsigned int slot_;
	std::string fileName_;
	GLuint id_;
	unsigned int width_;
	unsigned int height_;
	BYTE* pixels_;
};