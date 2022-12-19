#pragma once

#include "Pyro/Renderer/RendererAPI.h"

namespace Pyro
{
	class OpenGLRendererAPI : public RendererAPI
	{
	public:
		virtual void SetClearColor(const glm::vec4& color) override;
		virtual void Clear() override;

		virtual void DrawIndexed(Ref<VertexArray> vertexArray) override;
	};
}