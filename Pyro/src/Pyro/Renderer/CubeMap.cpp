#include "pypch.h"
#include "CubeMap.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLCubeMap.h"

namespace Pyro
{
	CubeMap* CubeMap::Create(const std::vector<std::string>& texLocs)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None: PY_CORE_ASSERT(false, "RenderAPI::None is not supported"); return nullptr;
			case RendererAPI::API::OpenGL: return new OpenGLCubeMap(texLocs);
		}

		PY_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}

}