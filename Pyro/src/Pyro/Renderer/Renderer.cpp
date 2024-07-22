#include "pypch.h"
#include "Renderer.h"

namespace Pyro
{
	Renderer::SceneData* Renderer::m_SceneData = new Renderer::SceneData;
	std::queue<Ref<Model>> Renderer::m_RenderQueue;

	void Renderer::BeginScene(Camera& camera)
	{
		m_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
		m_SceneData->CameraPosition = camera.GetPosition();
	}

	void Renderer::RenderScene()
	{
		std::vector<float> lightPositions;
		std::vector<float> lightColors;

		std::vector<float> lightConstantAtt;
		std::vector<float> lightLinearAtt;
		std::vector<float> lightQuadraticAtt;

		std::vector<float> lightDiffuseIntensity;
		std::vector<float> lightSpecularIntensity;

		for (Ref<PointLight> p : m_SceneData->Lights)
		{
			for (int i = 0; i < 3; i++)
			{
				lightPositions.push_back(p->GetLightData()->m_Pos[i]);
				lightColors.push_back(p->GetLightData()->m_Color[i]);
			}

			lightConstantAtt.push_back(p->GetLightData()->m_ConstantAtt);
			lightLinearAtt.push_back(p->GetLightData()->m_LinearAtt);
			lightQuadraticAtt.push_back(p->GetLightData()->m_QuadraticAtt);

			lightDiffuseIntensity.push_back(p->GetLightData()->m_DiffuseIntensity);
			lightSpecularIntensity.push_back(p->GetLightData()->m_SpecularIntensity);
		}

		while (!m_RenderQueue.empty())
		{
			for (Ref<Mesh> m : m_RenderQueue.front()->GetMeshes())
			{
				Ref<Shader> shader = m->GetMat()->GetShader();
				shader->Bind();
				shader->UploadUniformMat4("u_ViewProjection", m_SceneData->ViewProjectionMatrix);
				auto trans = m_RenderQueue.front()->GetTransform();
				trans->CheckPosChange();
				shader->UploadUniformMat4("u_Transform", *(trans));
				shader->UploadUniformFloat3("u_camPos", m_SceneData->CameraPosition);

				shader->UploadUniformInt("u_numLights", m_SceneData->LightCount);
				shader->UploadUniformFloat3Array("u_lightPositions", &(lightPositions[0]), m_SceneData->LightCount);
				shader->UploadUniformFloat3Array("u_lightColors", &(lightColors[0]), m_SceneData->LightCount);

				shader->UploadUniformFloat("u_metallic", m->GetMat()->GetMetallic());
				shader->UploadUniformFloat("u_roughness", m->GetMat()->GetRoughness());
				shader->UploadUniformFloat("u_ao", m->GetMat()->GetAO());

				//shader->UploadUniformFloat("u_Shininess", 0.01f);

				//shader->UploadUniformFloatArray("u_ConstAtt", &(lightConstantAtt[0]), m_SceneData->LightCount);
				//shader->UploadUniformFloatArray("u_LinAtt", &(lightLinearAtt[0]), m_SceneData->LightCount);
				//shader->UploadUniformFloatArray("u_QuadAtt", &(lightQuadraticAtt[0]), m_SceneData->LightCount);

				//shader->UploadUniformFloatArray("u_DifInt", &(lightDiffuseIntensity[0]), m_SceneData->LightCount);
				//shader->UploadUniformFloatArray("u_SpecInt", &(lightSpecularIntensity[0]), m_SceneData->LightCount);

				m->GetVertexArray()->Bind();
				m->GetMat()->GetTexture()->Bind();
				RenderCommand::DrawIndexed(m->GetVertexArray());
			}
			m_RenderQueue.pop();
		}

		m_SceneData->Lights.clear();
		m_SceneData->LightCount = 0;
	}

	void Renderer::Submit(Ref<Model> model)
	{
		m_RenderQueue.push(model);
	}

	void Renderer::SubmitLight(Ref<PointLight> light)
	{
		m_SceneData->Lights.push_back(light);
		m_SceneData->LightCount++;
	}
}