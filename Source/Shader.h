#pragma once

#include "GL/glew.h"
#include "Resource.h"

namespace ArenaBoss
{
	namespace Math
	{
		class Vector3;
		class Matrix4x4;
	}

	class Shader : public Resource
	{
		GENERATE_RESOURCE(Shader)

	public:
		Shader(const std::string& name) : Resource(name) {}

		Shader(const std::string& name,
			const std::string& vertName,
			const std::string& fragName);

		Shader(const Shader&) = delete;
		Shader(Shader&&) = default;

		Shader& operator=(const Shader&) = delete;
		Shader& operator=(Shader&&) = default;

		~Shader() override;

		bool Load(const std::string& vertName, const std::string& fragName);
		void Unload();

		void Activate();

		void SetUniformValue(const std::string& name, Math::Matrix4x4* matrices, uint32_t count);
		void SetUniformValue(const std::string& name, const Math::Matrix4x4& value);
		void SetUniformValue(const std::string& name, const Math::Vector3& value);
		void SetUniformValue(const std::string& name, float value);

	private:
		bool CompileShader(const std::string& fileName, GLenum shaderType, GLuint& outShader);
		bool IsCompiled(GLuint shader);
		bool IsValidProgram();

	private:
		GLuint vertexShader = 0u;
		GLuint fragShader = 0u;
		GLuint shaderProgram = 0u;
	};
}