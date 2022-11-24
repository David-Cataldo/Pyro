#include "pypch.h"
#include "Renderer.h"

namespace Pyro
{
	Renderer::SceneData* Renderer::m_SceneData = new Renderer::SceneData;

	void Renderer::BeginScene(Camera& camera)
	{
		m_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
	}

	void Renderer::EndScene()
	{
	}

	void Renderer::Submit(const Ref<Model>& model)
	{
		for (Ref<Mesh> m : model->GetMeshes())
		{
			m->GetMat()->GetShader()->Bind();
			m->GetMat()->GetShader()->UploadUniformMat4("u_ViewProjection", m_SceneData->ViewProjectionMatrix);
			m->GetMat()->GetShader()->UploadUniformMat4("u_Transform", *(model->GetTransform()));


			m->GetVertexArray()->Bind();
			m->GetMat()->GetTexture()->Bind();
			RenderCommand::DrawIndexed(m->GetVertexArray());
		}
	}
}