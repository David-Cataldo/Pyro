#include "pypch.h"
#include "Buffer.h"

#include "Renderer.h"

#include "Platform/OpenGL/OpenGLBuffer.h"

namespace Pyro
{
	VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::None: PY_CORE_ASSERT(false, "RenderAPI::None is not supported"); return nullptr;
			case RendererAPI::OpenGL: return new OpenGLVertexBuffer(vertices,size);
		}

		PY_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}

	IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::None: PY_CORE_ASSERT(false, "RenderAPI::None is not supported"); return nullptr;
			case RendererAPI::OpenGL: return new OpenGLIndexBuffer(indices, size);
		}

		PY_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}
}