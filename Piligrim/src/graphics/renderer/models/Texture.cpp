#include "Texture.h"

namespace piligrim {
	namespace graphics {



		Texture::Texture()
		{
		}



		Texture::Texture(std::string fileName)
		{
			load(fileName);
		}



		void Texture::bind() const
		{
			GLCall(glActiveTexture(GL_TEXTURE0 + slot));
			GLCall(glBindTexture(GL_TEXTURE_2D, id_));
		}



		void Texture::unbind() const
		{
			GLCall(glBindTexture(GL_TEXTURE_2D, 0));
		}



		GLuint Texture::getId() const
		{
			return id_;
		}



		unsigned int Texture::getWidth() const
		{
			return width_;
		}



		unsigned int Texture::getHeight() const
		{
			return height_;
		}



		void Texture::texDelete() const
		{
			GLCall(glDeleteTextures(1, &id_));
		}



		void Texture::load(std::string fileName)
		{
			fileName_ = fileName;
			pixels_ = ImageLoader::load(fileName_, width_, height_);

			GLCall(glGenTextures(1, &id_));
			GLCall(glBindTexture(GL_TEXTURE_2D, id_));

			GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
			GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));

			GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width_, height_, 0, GL_BGR, GL_UNSIGNED_BYTE, pixels_));

			GLCall(glBindTexture(GL_TEXTURE_2D, 0));
		}



	}
}