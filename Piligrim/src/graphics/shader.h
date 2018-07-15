#pragma once

#include <string>
#include <GL/glew.h>
#include "../math/math.h"
#include "../utils/fileutils.h"

namespace piligrim {
	namespace graphics {

		class Shader 
		{
		private:
			GLuint shader = 0;
			const char* vertPath;
			const char* fragPath;
		public:
			Shader(const char *vertPath, const char *fragmPath);
			Shader(const char *vertPath, const char *fragmPath, std::string& errorMessage);
			~Shader();

			void enable() const;
			void disable() const;

			GLuint id() const;
			bool isOk() const;

			GLint getUniformLocation(const GLchar* name);

			void setUniform(const GLchar* name, float value);
			void setUniform(const GLchar* name, int value);
			void setUniform(const GLchar* name, const math::vec2& vector);
			void setUniform(const GLchar* name, const math::vec3& vector);
			void setUniform(const GLchar* name, const math::vec4& vector);
			void setUniform(const GLchar* name, const math::mat4& matrix);

		private:
			GLuint load(std::string & errorMessage);
		};

	}
}