#pragma once

#include "Pyro/Renderer/Texture.h"

namespace Pyro
{
	class OpenGLTexture : public Texture
	{
	public:
		OpenGLTexture(const std::string& fileLoc);
		OpenGLTexture();
		virtual ~OpenGLTexture() override;

		virtual bool LoadTexture() override;
		virtual bool LoadTextureAlpha() override;

		virtual void Bind() override;
		virtual void Unbind() override;
		virtual void ClearTexture() override;

		static bool LoadPlainTexture();

	private:
		uint32_t m_TextureID;
		std::string m_FileLoc;

		static uint32_t s_PlainTextureID;

	};
}