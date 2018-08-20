#include "shader.h"
#include <vector>




Shader::Shader()
{
}



Shader::Shader(std::string vertPath, std::string fragmPath)
	:vertPath_(vertPath), fragPath_(fragmPath)
{
}



Shader::~Shader()
{
	glDeleteShader(shader_);
}



void Shader::compile(std::string& errorMessage)
{
	shader_ = load(errorMessage);
}



void Shader::enable() const
{
	GLCall(glUseProgram(shader_));
}



void Shader::disable() const
{
	GLCall(glUseProgram(0));
}



GLuint Shader::getId() const
{
	return shader_;
}



bool Shader::isOk() const
{
	return shader_ != 0;
}



GLint Shader::getUniformLocation(const GLchar * name)
{
	std::string strName(name);
	auto uniform = uniformsCache_.find(strName);

	if (uniform != uniformsCache_.end()) {
		return uniform->second;
	}

	uniformsCache_[strName] = glGetUniformLocation(shader_, name);

	return uniformsCache_[strName];
}



void Shader::setUniform(const GLchar * name, float value)
{
	GLCall(glUniform1f(getUniformLocation(name), value));
}



void Shader::setUniform(const GLchar * name, int value)
{
	GLCall(glUniform1i(getUniformLocation(name), value));
}



void Shader::setUniform(const GLchar * name, const vec2 & vector)
{
	GLCall(glUniform2f(getUniformLocation(name), vector.x, vector.y));
}



void Shader::setUniform(const GLchar * name, const vec3 & vector)
{
	GLCall(glUniform3f(getUniformLocation(name), vector.x, vector.y, vector.z));
}



void Shader::setUniform(const GLchar * name, const vec4 & vector)
{
	GLCall(glUniform4f(getUniformLocation(name), vector.x, vector.y, vector.z, vector.w));
}



void Shader::setUniform(const GLchar * name, const mat4 & matrix)
{
	GLCall(glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, matrix.elements));
}



void Shader::setUniform(const std::string& name, const Material & material)
{
	setUniform(
		(name + ".diffuse").c_str(),
		static_cast<int>(material.diffuse->getSlot())
	);

	setUniform(
		(name + ".specular").c_str(),
		static_cast<int>(material.specular->getSlot())
	);

	setUniform(
		(name + ".shininess").c_str(),
		material.shininess
	);
}

void Shader::setUniform(const std::string& name, const Light& light)
{
	setUniform(
		(name + ".position").c_str(),
		light.position
	);

	setUniform(
		(name + ".ambient").c_str(),
		light.ambient
	);

	setUniform(
		(name + ".diffuse").c_str(),
		light.diffuse
	);

	setUniform(
		(name + ".specular").c_str(),
		light.specular
	);
}



GLuint Shader::load(std::string& errorMessage)
{
	GLCall(GLuint program = glCreateProgram());
	GLCall(GLuint vertex = glCreateShader(GL_VERTEX_SHADER));
	GLCall(GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER));

	std::string vertexCodeString = FileUtils::readFile(vertPath_);
	std::string fragmentCodeString = FileUtils::readFile(fragPath_);

	const char * vertCode = vertexCodeString.c_str();
	const char * fragCode = fragmentCodeString.c_str();

	if (!compileShader(vertex, vertCode, errorMessage, "[Vertex Shader] Compile error | ")) {
		return 0;
	}

	if (!compileShader(fragment, fragCode, errorMessage, "[Fragment Shader] Compile error | ")) {
		return 0;
	}

	if (!linkProgram(program, vertex, fragment, errorMessage, "[Program Shader] Link error | ")) {
		return 0;
	}

	GLCall(glDeleteShader(vertex));
	GLCall(glDeleteShader(fragment));

	errorMessage = "[Shader's compile succesfull!]";

	return program;
}



bool Shader::compileShader(GLuint shader, const char* code, std::string & errorMessage, const std::string & errorPrefix)
{
	GLCall(glShaderSource(shader, 1, &code, NULL));
	GLCall(glCompileShader(shader));

	GLint result;

	GLCall(glGetShaderiv(shader, GL_COMPILE_STATUS, &result));

	if (result == GL_FALSE)
	{
		errorMessage = errorPrefix + getShaderErrorMessage(shader);
		GLCall(glDeleteShader(shader));

		return false;
	}

	return true;
}



bool Shader::linkProgram(GLuint program, GLuint vertex, GLuint fragment, std::string& errorMessage, const std::string& errorPrefix)
{
	GLCall(glAttachShader(program, vertex));
	GLCall(glAttachShader(program, fragment));

	GLCall(glLinkProgram(program));
	GLCall(glValidateProgram(program));

	GLint result;

	GLCall(glGetProgramiv(program, GL_LINK_STATUS, &result));

	if (result == GL_FALSE)
	{
		errorMessage = errorPrefix + getProgramErrorMessage(program);

		return false;
	}

	return true;
}



std::string Shader::getShaderErrorMessage(GLuint shader)
{
	GLint length;

	GLCall(glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length));
	std::vector<char> error(length);
	GLCall(glGetShaderInfoLog(shader, length, &length, &error[0]));

	return std::string(&error[0]);
}



std::string Shader::getProgramErrorMessage(GLuint program)
{
	GLint length;

	GLCall(glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length));
	std::vector<char> error(length);
	GLCall(glGetProgramInfoLog(program, length, &length, &error[0]));

	return std::string(&error[0]);
}