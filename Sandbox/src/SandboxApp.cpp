#include <Pyro.h>

#include <glm/gtc/matrix_transform.hpp>

class ExampleLayer : public Pyro::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), m_CameraController(45.0f, 1.6 / 0.9, 0.1f, 1000.0f)
	{		

		Pyro::Texture::LoadPlainTexture();
		m_CameraController.SetPosition(glm::vec3(0.0f, 50.0f, 0.0f));

		pl1.reset(new Pyro::PointLight(glm::vec3(0.0f, 50.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), 0.3f, 0.2f, 0.1f, 500.0f, 10.0f));
		pl2.reset(new Pyro::PointLight(glm::vec3(6.0f, 2.0f, 3.0f), glm::vec3(1.0f, 0.0f, 0.0f)));
		pl3.reset(new Pyro::PointLight(glm::vec3(-1.0f, 1.0f, -3.0f)));

		m_Model.reset(new Pyro::Model("Assets/Models/tree.obj"));
		m_Model->GetTransform()->SetPos(glm::vec3(0.0f, 0.0f, 0.0f));
		m_Model->GetPhys()->m_gravEnabled = false;

		//std::cout << m_Model->GetName() << std::endl;
		//std::cout << pl1->GetName() << std::endl;
		//std::cout << pl2->GetName() << std::endl;
	}

	void OnUpdate(Pyro::Timestep ts) override
	{
		m_CameraController.OnUpdate(ts);
		

		Pyro::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Pyro::RenderCommand::Clear();

		Pyro::PhysicsEngine::Submit(m_Model->GetPhys());


		Pyro::Renderer::BeginScene(m_CameraController.GetCamera());

		Pyro::Renderer::SubmitLight(pl1);
		Pyro::Renderer::SubmitLight(pl2);
		Pyro::Renderer::SubmitLight(pl3);

		m_Model->GetTransform()->Translate(glm::vec3(0.05f * ts, 0.05f * ts, 0.05f * ts));

		Pyro::Renderer::Submit(m_Model);

		Pyro::PhysicsEngine::UpdatePhysics(ts);
		Pyro::Renderer::RenderScene();

	}

	void OnImGuiRender() override
	{
		//imgui->OnImGuiRender();
	}
	
	void OnEvent(Pyro::Event& evnt) override
	{
		//imgui->OnEvent(evnt);
		//if(!evnt.Handled)
		m_CameraController.OnEvent(evnt);
	}

	~ExampleLayer()
	{
		//imgui->OnDetach();
	}

	

private:
	Pyro::Ref<Pyro::Model> m_Model;
	Pyro::PerspectiveCameraController m_CameraController;
	Pyro::Ref<Pyro::PointLight> pl1;
	Pyro::Ref<Pyro::PointLight> pl2;
	Pyro::Ref<Pyro::PointLight> pl3;

	Pyro::Ref<Pyro::ImGuiLayer> imgui;
};

class Sandbox : public Pyro::Application
{
public:
	Sandbox() 
		: Application()
	{
		PushLayer(new ExampleLayer());
	}

	~Sandbox() {}


};


Pyro::Application* Pyro::CreateApplication()
{
	return new Sandbox();
}