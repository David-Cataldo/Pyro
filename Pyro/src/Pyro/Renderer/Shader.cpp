#include "pypch.h"
#include "Shader.h"

#include "Renderer.h"

#include "Platform/OpenGL/OpenGLShader.h"

namespace Pyro
{
	Shader* Shader::Create(const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::None: PY_CORE_ASSERT(false, "RenderAPI::None is not supported"); return nullptr;
		case RendererAPI::OpenGL: return new OpenGLShader(vertexSrc, fragmentSrc);
		}

		PY_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}
}