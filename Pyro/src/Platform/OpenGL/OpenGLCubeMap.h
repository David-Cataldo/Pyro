#pragma once

#include "Pyro/Renderer/CubeMap.h"

namespace Pyro
{
	class OpenGLCubeMap : public CubeMap
	{
	public:
		OpenGLCubeMap(const std::vector<std::string>& texLocs);
		OpenGLCubeMap();
		virtual ~OpenGLCubeMap();

		virtual bool LoadTexture() override;
		virtual bool LoadTextureAlpha() override;

		virtual void Bind() override;
		virtual void Unbind() override;
		virtual void ClearTexture() override;

	private:
		uint32_t m_TextureID;
		std::vector<std::string> m_TexLocs;
	};
}