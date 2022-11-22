#pragma once

#include <string>
#include <glm/glm.hpp>

namespace Pyro
{
	class Shader
	{
	public:
		virtual ~Shader() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		static Shader* Create(const std::string& vertexSrc, const std::string& fragmentSrc);


		virtual void UploadUniformFloat(const std::string& name, float val) = 0;
		virtual void UploadUniformFloat2(const std::string& name, const glm::vec2& vec) = 0;
		virtual void UploadUniformFloat3(const std::string& name, const glm::vec3& vec) = 0;
		virtual void UploadUniformFloat4(const std::string& name, const glm::vec4& vec) = 0;

		virtual void UploadUniformMat3(const std::string& name, const glm::mat3& matrix) = 0;
		virtual void UploadUniformMat4(const std::string& name, const glm::mat4& matrix) = 0;

		virtual void UploadUniformInt(const std::string& name, int val) = 0;
		virtual void UploadUniformInt2(const std::string& name, const glm::ivec2& vec) = 0;
		virtual void UploadUniformInt3(const std::string& name, const glm::ivec3& vec) = 0;
		virtual void UploadUniformInt4(const std::string& name, const glm::ivec4& vec) = 0;

		virtual void UploadUniformBool(const std::string& name, bool val) = 0;

	};
}