#include "pypch.h"
#include "Texture.h"

#include "Renderer.h"

#include "Platform/OpenGL/OpenGLTexture.h"

namespace Pyro
{
	Texture* Texture::Create(const std::string& fileLoc)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None: PY_CORE_ASSERT(false, "RenderAPI::None is not supported"); return nullptr;
			case RendererAPI::API::OpenGL: return new OpenGLTexture(fileLoc);
		}

		PY_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}

	void Texture::LoadPlainTexture()
	{
		OpenGLTexture::LoadPlainTexture();
	}
}