#pragma once

#include <queue>

#include "RenderCommand.h"
#include "OrthographicCamera.h"

#include "Model.h"
#include "PointLight.h"

namespace Pyro
{
	

	class Renderer
	{
	public:
		static void BeginScene(Camera& camera);
		static void RenderScene();

		static void Submit(Ref<Model> model);
		static void SubmitLight(Ref<PointLight> light);

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

	private:
		struct SceneData
		{
			glm::mat4 ViewProjectionMatrix;
			glm::vec3 CameraPosition;
			std::vector<Ref<PointLight>> Lights;
			unsigned int LightCount = 0;
		};

		static SceneData* m_SceneData;
		static std::queue<Ref<Model>> m_RenderQueue;
	};

}