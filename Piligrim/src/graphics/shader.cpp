#include "shader.h"
#include <vector>

piligrim::graphics::Shader::Shader(const char * vertPath, const char * fragmPath)
	:vertPath(vertPath), fragPath(fragmPath)
{
	std::string empty;
	shader = load(empty);
}

piligrim::graphics::Shader::Shader(const char * vertPath, const char * fragmPath, std::string& errorMessage)
	:vertPath(vertPath), fragPath(fragmPath)
{
	shader = load(errorMessage);
}

piligrim::graphics::Shader::~Shader()
{
	glDeleteShader(shader);
}

void piligrim::graphics::Shader::enable() const
{
	glUseProgram(shader);
}

void piligrim::graphics::Shader::disable() const
{
	glUseProgram(0);
}

GLuint piligrim::graphics::Shader::id() const
{
	return shader;
}

bool piligrim::graphics::Shader::isOk() const
{
	return shader != 0;
}

GLint piligrim::graphics::Shader::getUniformLocation(const GLchar * name)
{
	return glGetUniformLocation(shader, name);
}

void piligrim::graphics::Shader::setUniform(const GLchar * name, float value)
{
	glUniform1f(getUniformLocation(name), value);
}

void piligrim::graphics::Shader::setUniform(const GLchar * name, int value)
{
	glUniform1i(getUniformLocation(name), value);
}

void piligrim::graphics::Shader::setUniform(const GLchar * name, const math::vec2 & vector)
{
	glUniform2f(getUniformLocation(name), vector.x, vector.y);
}

void piligrim::graphics::Shader::setUniform(const GLchar * name, const math::vec3 & vector)
{
	glUniform3f(getUniformLocation(name), vector.x, vector.y, vector.z);
}

void piligrim::graphics::Shader::setUniform(const GLchar * name, const math::vec4 & vector)
{
	glUniform4f(getUniformLocation(name), vector.x, vector.y, vector.z, vector.w);
}

void piligrim::graphics::Shader::setUniform(const GLchar * name, const math::mat4 & matrix)
{
	glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, matrix.elements);
}

GLuint piligrim::graphics::Shader::load(std::string& errorMessage)
{
	GLuint program = glCreateProgram();
	GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);

	std::string vertexCodeString = FileUtils::readFile(vertPath);
	std::string fragmentCodeString = FileUtils::readFile(fragPath);

	const char * vertCode = vertexCodeString.c_str();
	const char * fragCode = fragmentCodeString.c_str();
	
	glShaderSource(vertex, 1, &vertCode, NULL);
	glCompileShader(vertex);

	GLint result;
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE) 
	{
		GLint length;
		glGetShaderiv(vertex, GL_INFO_LOG_LENGTH, &length);
		std::vector<char> error(length);
		glGetShaderInfoLog(vertex, length, &length, &error[0]);
		errorMessage = "[Vertex Shader] Compile error | " + std::string(&error[0]);
		glDeleteShader(vertex);
		return 0;
	}

	glShaderSource(fragment, 1, &fragCode, NULL);
	glCompileShader(fragment);

	glGetShaderiv(fragment, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE)
	{
		GLint length;
		glGetShaderiv(fragment, GL_INFO_LOG_LENGTH, &length);
		std::vector<char> error(length);
		glGetShaderInfoLog(fragment, length, &length, &error[0]);
		errorMessage = "[Fragment Shader] Compile error | " + std::string(&error[0]);
		glDeleteShader(fragment);
		return 0;
	}
	glAttachShader(program, vertex);
	glAttachShader(program, fragment);

	glLinkProgram(program);
	glValidateProgram(program);

	glGetProgramiv(program, GL_LINK_STATUS, &result);
	if (result == GL_FALSE)
	{
		GLint length;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);
		std::vector<char> error(length);
		glGetProgramInfoLog(program, length, &length, &error[0]);
		errorMessage = "[Program Shader] Link error | " + std::string(&error[0]);
		return 0;
	}

	glDeleteShader(vertex);
	glDeleteShader(fragment);

	errorMessage = "[Shader's compile succesfull!]";

	return program;
}