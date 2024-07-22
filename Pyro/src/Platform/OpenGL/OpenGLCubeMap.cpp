#include "pypch.h"
#include "OpenGLCubeMap.h"

#include <glad/glad.h>

#include "../vendor/stbi/include/stb_image.h"

namespace Pyro
{
	OpenGLCubeMap::OpenGLCubeMap(const std::vector<std::string>& texLocs)
		: m_TexLocs(texLocs), m_TextureID(0)
	{
	}
	OpenGLCubeMap::OpenGLCubeMap()
		: m_TexLocs(std::vector<std::string>()), m_TextureID(0)
	{
	}

	OpenGLCubeMap::~OpenGLCubeMap()
	{
		ClearTexture();
	}

	bool OpenGLCubeMap::LoadTexture()
	{
		



		return false;
	}

	bool OpenGLCubeMap::LoadTextureAlpha()
	{
		return false;
	}

	void OpenGLCubeMap::Bind()
	{
	}

	void OpenGLCubeMap::Unbind()
	{
	}

	void OpenGLCubeMap::ClearTexture()
	{
	}
}