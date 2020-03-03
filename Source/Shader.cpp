#include "Shader.h"
#include <SDL2/SDL.h>
#include <fstream>
#include <sstream>
#include "Log.h"
#include "Matrix4x4.h"
#include "Vector3.h"

namespace ArenaBoss
{
	Shader::Shader(const std::string& name,
		const std::string& vertName,
		const std::string& fragName)
		: Resource(name)
	{
		Load(vertName, fragName);
	}

	Shader::~Shader()
	{
		if (IsValidProgram())
			Unload();
	}

	bool Shader::Load(const std::string& vertName, const std::string& fragName) {
		if (!CompileShader(vertName, GL_VERTEX_SHADER, vertexShader)
			|| !CompileShader(fragName, GL_FRAGMENT_SHADER, fragShader))
			return false;

		shaderProgram = glCreateProgram();
		glAttachShader(shaderProgram, vertexShader);
		glAttachShader(shaderProgram, fragShader);
		glLinkProgram(shaderProgram);

		return IsValidProgram();
	}

	void Shader::Unload() {
		glDeleteProgram(shaderProgram);
		glDeleteShader(fragShader);
		glDeleteShader(vertexShader);
	}

	void Shader::Activate() {
		glUseProgram(shaderProgram);
	}

	void Shader::SetUniformValue(const std::string& name, Math::Matrix4x4* matrices, uint32_t count) {
		GLuint loc = glGetUniformLocation(shaderProgram, name.c_str());
		glUniformMatrix4fv(loc, count, GL_TRUE, reinterpret_cast<const GLfloat*>(matrices));
	}

	void Shader::SetUniformValue(const std::string& name, const Math::Matrix4x4& value) {
		const auto loc = glGetUniformLocation(shaderProgram, name.c_str());
		glUniformMatrix4fv(loc, 1, GL_TRUE, static_cast<const GLfloat*>(value));
	}

	void Shader::SetUniformValue(const std::string& name, const Math::Vector3& value) {
		const auto loc = glGetUniformLocation(shaderProgram, name.c_str());
		glUniform3fv(loc, 1, static_cast<const GLfloat*>(value));
	}

	void Shader::SetUniformValue(const std::string& name, const float value) {
		const auto loc = glGetUniformLocation(shaderProgram, name.c_str());
		glUniform1f(loc, value);
	}

	bool Shader::CompileShader(const std::string& fileName, GLenum shaderType, GLuint& outShader) {
		std::ifstream shaderFile{ fileName };

		if (!shaderFile.is_open()) {
			Log("Shader file not found: %s", fileName.c_str());
			return false;
		}

		std::stringstream sstream;
		sstream << shaderFile.rdbuf();
		const auto contents = sstream.str();
		const auto* contentsChar = contents.c_str();

		outShader = glCreateShader(shaderType);
		glShaderSource(outShader, 1, &contentsChar, nullptr);
		glCompileShader(outShader);

		if (!IsCompiled(outShader)) {
			Log("Failed to compile shader %s", fileName.c_str());
			return false;
		}

		return true;
	}

	bool Shader::IsCompiled(GLuint shader) {
		GLint status;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
		return status == GL_TRUE;
	}

	bool Shader::IsValidProgram() {
		GLint status;
		glGetProgramiv(shaderProgram, GL_LINK_STATUS, &status);
		return status == GL_TRUE;
	}
}