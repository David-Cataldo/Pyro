#pragma once

#include "RenderCommand.h"
#include "OrthographicCamera.h"

#include "Model.h"

namespace Pyro
{
	

	class Renderer
	{
	public:
		static void BeginScene(Camera& camera);
		static void EndScene();

		static void Submit(const Ref<Model>& model);

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

	private:
		struct SceneData
		{
			glm::mat4 ViewProjectionMatrix;
		};

		static SceneData* m_SceneData;
	};

}