#include <Pyro.h>

#include <glm/gtc/matrix_transform.hpp>

class ExampleLayer : public Pyro::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), m_CameraController(45.0f, 1.6/0.9, 0.1f, 100.0f)
	{
		m_VertexArray.reset(Pyro::VertexArray::Create());

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
			 0.0f,	0.5f, 0.0f, 0.8f, 0.8f, 0.3f, 1.0f
		};

		Pyro::Ref<Pyro::VertexBuffer> m_VertexBuffer;
		m_VertexBuffer.reset(Pyro::VertexBuffer::Create(vertices, sizeof(vertices)));

		Pyro::BufferLayout layout = {
			{ Pyro::ShaderDataType::Float3, "a_Position"},
			{ Pyro::ShaderDataType::Float4, "a_Color"}
		};

		m_VertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(m_VertexBuffer);


		uint32_t indices[3] = {
			0, 1, 2
		};

		Pyro::Ref<Pyro::IndexBuffer> m_IndexBuffer;
		m_IndexBuffer.reset(Pyro::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));

		m_VertexArray->SetIndexBuffer(m_IndexBuffer);



		m_SquareVA.reset(Pyro::VertexArray::Create());

		float vertices2[8 * 3]{
		-1, -1,  0.5, //0
		 1, -1,  0.5, //1
		-1,  1,  0.5, //2
		 1,  1,  0.5, //3
		-1, -1, -0.5, //4
		 1, -1, -0.5, //5
		-1,  1, -0.5, //6
		 1,  1, -0.5  //7
		};

		Pyro::Ref<Pyro::VertexBuffer> squareVB;
		squareVB.reset(Pyro::VertexBuffer::Create(vertices2, sizeof(vertices2)));


		squareVB->SetLayout({
				{ Pyro::ShaderDataType::Float3, "a_Position"}
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

		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}

		)";

		std::string fragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;
			in vec4 v_Color;

			void main()
			{
				color = v_Color;
			}

		)";

		m_Shader.reset(Pyro::Shader::Create(vertexSrc, fragmentSrc));

		std::string vertexSrc2 = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position;
			    gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);

			}

		)";

		std::string fragmentSrc2 = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;

			void main()
			{
				color = vec4(0.0, 0.0, 1.0, 1.0);
			}

		)";

		m_Shader2.reset(Pyro::Shader::Create(vertexSrc2, fragmentSrc2));
	}

	void OnUpdate(Pyro::Timestep ts) override
	{

		m_CameraController.OnUpdate(ts);
		


		Pyro::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Pyro::RenderCommand::Clear();


		Pyro::Renderer::BeginScene(m_CameraController.GetCamera());


		Pyro::Renderer::Submit(m_SquareVA, m_Shader2);
		Pyro::Renderer::Submit(m_VertexArray, m_Shader);

		Pyro::Renderer::EndScene();
	}
	
	void OnEvent(Pyro::Event& evnt) override
	{
		m_CameraController.OnEvent(evnt);
		
	}

private:
	Pyro::Ref<Pyro::Shader> m_Shader;
	Pyro::Ref<Pyro::VertexArray> m_VertexArray;

	Pyro::Ref<Pyro::Shader> m_Shader2;
	Pyro::Ref<Pyro::VertexArray> m_SquareVA;

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