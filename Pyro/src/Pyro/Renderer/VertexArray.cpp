#include "pypch.h"
#include "VertexArray.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Pyro
{
	VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::None: PY_CORE_ASSERT(false, "RenderAPI::None is not supported"); return nullptr;
		case RendererAPI::OpenGL: return new OpenGLVertexArray();
		}

		PY_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}
}