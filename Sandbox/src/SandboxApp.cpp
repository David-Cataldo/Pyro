#include <Pyro.h>

#include <glm/gtc/matrix_transform.hpp>

class ExampleLayer : public Pyro::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), m_CameraController(45.0f, 1.6/0.9, 0.1f, 100.0f)
	{

		Pyro::Ref<Pyro::TransformComponent> m_Transform;
		Pyro::Ref<Pyro::Material> m_Mat;
		Pyro::Ref<Pyro::VertexArray> m_SquareVA;
		Pyro::Ref<Pyro::Mesh> m_Mesh;

		m_SquareVA.reset(Pyro::VertexArray::Create());

		float vertices2[8 * 5]{
		-1, -1,  0.5, -1, -1,//0
		 1, -1,  0.5,  1, -1,//1
		-1,  1,  0.5, -1,  1,//2
		 1,  1,  0.5,  1,  1,//3
		-1, -1, -0.5, -1, -1,//4
		 1, -1, -0.5,  1, -1,//5
		-1,  1, -0.5, -1,  1,//6
		 1,  1, -0.5,  1,  1//7
		};

		Pyro::Ref<Pyro::VertexBuffer> squareVB;
		squareVB.reset(Pyro::VertexBuffer::Create(vertices2, sizeof(vertices2)));


		squareVB->SetLayout({
				{ Pyro::ShaderDataType::Float3, "a_Position"},
				{ Pyro::ShaderDataType::Float2, "a_TextureCoords"}
			});
		m_SquareVA->AddVertexBuffer(squareVB);

		uint32_t indices2[6 * 6]{
			//Top
			2, 6, 7,
			2, 3, 7,

			//Bottom
			0, 4, 5,
			0, 1, 5,

			//Left
			0, 2, 6,
			0, 4, 6,

			//Right
			1, 3, 7,
			1, 5, 7,

			//Front
			0, 2, 3,
			0, 1, 3,

			//Back
			4, 6, 7,
			4, 5, 7
		};


		Pyro::Ref<Pyro::IndexBuffer> squareIB;
		squareIB.reset(Pyro::IndexBuffer::Create(indices2, sizeof(indices2)));

		m_SquareVA->SetIndexBuffer(squareIB);

		
		Pyro::Ref<Pyro::Shader> m_Shader2;
		m_Shader2.reset(Pyro::Shader::Create("Assets/Shaders/Test.vert.txt", "Assets/Shaders/Test.frag.txt"));
		m_Transform.reset(new Pyro::TransformComponent(glm::mat4(1.0f)));

		Pyro::Ref<Pyro::Texture> m_Tex;
		m_Tex.reset(Pyro::Texture::Create("Assets/Textures/brick.png"));

		m_Mat.reset(new Pyro::Material(m_Shader2, m_Tex));

		m_Mesh.reset(new Pyro::Mesh());
		m_Mesh->Create(m_SquareVA, m_Mat, m_Transform);
		m_Mesh->GetMat()->GetTexture()->LoadTextureAlpha();

		std::vector<Pyro::Ref<Pyro::Mesh>> meshes;
		meshes.push_back(m_Mesh);
		m_Model.reset(new Pyro::Model(meshes));
	}

	void OnUpdate(Pyro::Timestep ts) override
	{

		m_CameraController.OnUpdate(ts);
		


		Pyro::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Pyro::RenderCommand::Clear();


		Pyro::Renderer::BeginScene(m_CameraController.GetCamera());

		Pyro::Renderer::Submit(m_Model);
		(*m_Model)[0]->GetTransform()->Translate(glm::vec3(0.1f * ts, 0.0f, 0.0f));
		Pyro::Renderer::EndScene();
	}
	
	void OnEvent(Pyro::Event& evnt) override
	{
		m_CameraController.OnEvent(evnt);
	}

private:
	Pyro::Ref<Pyro::Model> m_Model;
	Pyro::PerspectiveCameraController m_CameraController;
};

class Sandbox : public Pyro::Application
{
public:
	Sandbox() 
	{
		PushLayer(new ExampleLayer());
	}

	~Sandbox() {}
};


Pyro::Application* Pyro::CreateApplication()
{
	return new Sandbox();
}