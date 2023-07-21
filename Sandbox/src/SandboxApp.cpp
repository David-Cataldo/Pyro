#include <Pyro.h>

#include <glm/gtc/matrix_transform.hpp>

class ExampleLayer : public Pyro::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), m_CameraController(45.0f, 1.6 / 0.9, 0.1f, 100.0f)
	{		

		Pyro::Texture::LoadPlainTexture();
		m_CameraController.SetPosition(glm::vec3(-14.405, -1.60766, -5.88903));

		Pyro::Ref<Pyro::TransformComponent> m_Transform;
		Pyro::Ref<Pyro::Material> m_Mat;
		Pyro::Ref<Pyro::VertexArray> m_SquareVA;
		Pyro::Ref<Pyro::Mesh> m_Mesh;

		m_SquareVA.reset(Pyro::VertexArray::Create());

		float vertices2[4 * 3] = {
			//-50, -6, -50, -1, -1, 0.0f, -1.0f, 0.0f,
			-50, -1, -50,	// 1, -1,	0.0f, 1.0f, 0.0f,
			 50, -1, -50,	//-1,  1,	0.0f, 1.0f, 0.0f,
			 // 50, -6, -50,	 1,  1,	0.0f, -1.0f, 0.0f,
			 //-50, -6,  50,	-1, -1,	0.0f, -1.0f, 0.0f,
			 -50, -1,  50,	// 1, -1,	0.0f, 1.0f, 0.0f,
			  50, -1,  50	//-1,  1,	0.0f, 1.0f, 0.0f
			  // 50, -6,  50,	 1,  1,	0.0f, -1.0f, 0.0f
		};

		float normals[4 * 3]
		{
			0.0f, 1.0f, 0.0f,
			0.0f, 1.0f, 0.0f,
			0.0f, 1.0f, 0.0f,
			0.0f, 1.0f, 0.0f
		};

		float texCoords[4 * 2]
		{
			 1, -1,
			-1,  1,
			 1, -1,
			-1,  1
		};



		pl1.reset(new Pyro::PointLight(glm::vec3(1.0f, 0.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f), 0.3f, 0.2f, 0.1f, 1.0f, 10.0f));
		pl2.reset(new Pyro::PointLight(glm::vec3(6.0f, 2.0f, 3.0f), glm::vec3(1.0f, 0.0f, 0.0f)));
		pl3.reset(new Pyro::PointLight(glm::vec3(-1.0f, 1.0f, -3.0f)));

		uint32_t indices[6] = {
			0, 2, 3,
			3, 1, 0
		};

		Pyro::Ref<Pyro::VertexBuffer> squareVB;
		squareVB.reset(Pyro::VertexBuffer::Create(vertices2, sizeof(vertices2)));


		squareVB->SetLayout({
				{ Pyro::ShaderDataType::Float3, "a_Position"}
			});

		Pyro::Ref<Pyro::VertexBuffer> squareVB1;
		squareVB1.reset(Pyro::VertexBuffer::Create(normals, sizeof(normals)));


		squareVB1->SetLayout({
				{ Pyro::ShaderDataType::Float3, "a_Normal"}
			});

		Pyro::Ref<Pyro::VertexBuffer> squareVB2;
		squareVB2.reset(Pyro::VertexBuffer::Create(texCoords, sizeof(texCoords)));


		squareVB2->SetLayout({
				{ Pyro::ShaderDataType::Float2, "a_TextureCoords"}
			});



		m_SquareVA->AddVertexBuffer(squareVB);
		m_SquareVA->AddVertexBuffer(squareVB2);
		m_SquareVA->AddVertexBuffer(squareVB1);

		
		Pyro::Ref<Pyro::IndexBuffer> squareIB;
		squareIB.reset(Pyro::IndexBuffer::Create(indices, sizeof(indices)));

		m_SquareVA->SetIndexBuffer(squareIB);

		
		Pyro::Ref<Pyro::Shader> m_Shader2;
		m_Shader2.reset(Pyro::Shader::Create("Assets/Shaders/Test.vert.txt", "Assets/Shaders/PBR.frag.txt"));
		m_Transform.reset(new Pyro::TransformComponent(glm::mat4(1.0f)));

		Pyro::Ref<Pyro::Texture> m_Tex;
		m_Tex.reset(Pyro::Texture::CreatePlain());

		m_Mat.reset(new Pyro::Material(m_Shader2, m_Tex, 0.1, 0.1, 0.0));


		Pyro::Ref<Pyro::ImGUIComponent> metComp;
		metComp.reset(Pyro::ImGUIComponent::CreateSlider("Metallic", m_Mat->GetMetallic(), 0.0f, 1.0f));
		imgui.reset(new Pyro::ImGuiLayer());
		imgui->AddComponent(metComp);

		Pyro::Ref<Pyro::ImGUIComponent> roughComp;
		roughComp.reset(Pyro::ImGUIComponent::CreateSlider("Roughness", m_Mat->GetRoughness(), 0.0f, 1.0f));
		imgui->AddComponent(roughComp);

		Pyro::Ref<Pyro::ImGUIComponent> aoComp;
		aoComp.reset(Pyro::ImGUIComponent::CreateSlider("AO", m_Mat->GetAO(), 0.0f, 1.0f));
		imgui->AddComponent(aoComp);

		m_Mesh.reset(new Pyro::Mesh());
		m_Mesh->Create(m_SquareVA, m_Mat);
		m_Mesh->GetMat()->GetTexture()->LoadTexture();

		std::vector<Pyro::Ref<Pyro::Mesh>> meshes;
		meshes.push_back(m_Mesh);
		m_Model.reset(new Pyro::Model(meshes));
		
		
		m_Model.reset(new Pyro::Model("Assets/Models/untitled.obj"));

		//std::cout << m_Model->GetName() << std::endl;
		//std::cout << pl1->GetName() << std::endl;
		//std::cout << pl2->GetName() << std::endl;
	}

	void OnUpdate(Pyro::Timestep ts) override
	{
		m_CameraController.OnUpdate(ts);
		

		Pyro::RenderCommand::SetClearColor({ 0.1f, 0.1f, 1.0f, 1 });
		Pyro::RenderCommand::Clear();


		Pyro::Renderer::BeginScene(m_CameraController.GetCamera());

		Pyro::Renderer::SubmitLight(pl1);
		Pyro::Renderer::SubmitLight(pl2);
		Pyro::Renderer::SubmitLight(pl3);


		Pyro::Renderer::Submit(m_Model);
		Pyro::Renderer::RenderScene();

	}

	void OnImGuiRender() override
	{
		imgui->OnImGuiRender();
	}
	
	void OnEvent(Pyro::Event& evnt) override
	{
		imgui->OnEvent(evnt);
		if(!evnt.Handled)
			m_CameraController.OnEvent(evnt);
	}

	~ExampleLayer()
	{
		imgui->OnDetach();
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