#pragma once

#include "Pyro/Renderer/Shader.h"

namespace Pyro
{
	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc);
		virtual ~OpenGLShader() override;

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void UploadUniformFloat(const std::string& name, float val) override;
		virtual void UploadUniformFloat2(const std::string& name, const glm::vec2& vec) override;
		virtual void UploadUniformFloat3(const std::string& name, const glm::vec3& vec) override;
		virtual void UploadUniformFloat4(const std::string& name, const glm::vec4& vec) override;

		virtual void UploadUniformMat3(const std::string& name, const glm::mat3& matrix) override;
		virtual void UploadUniformMat4(const std::string& name, const glm::mat4& matrix) override;

		virtual void UploadUniformInt(const std::string& name, int val) override;
		virtual void UploadUniformInt2(const std::string& name, const glm::ivec2& vec) override;
		virtual void UploadUniformInt3(const std::string& name, const glm::ivec3& vec) override;
		virtual void UploadUniformInt4(const std::string& name, const glm::ivec4& vec) override;

		virtual void UploadUniformBool(const std::string& name, bool val) override;	
	
	private:
		uint32_t m_RendererID;
		mutable bool m_Bound = false;
	};
}