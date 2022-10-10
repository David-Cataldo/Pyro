#include <Pyro.h>

#include <glm/gtc/matrix_transform.hpp>

class ExampleLayer : public Pyro::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(0.0f), m_SquarePos(0.0f)
	{
		m_VertexArray.reset(Pyro::VertexArray::Create());

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
			 0.0f,	0.5f, 0.0f, 0.8f, 0.8f, 0.3f, 1.0f
		};

		std::shared_ptr<Pyro::VertexBuffer> m_VertexBuffer;
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

		std::shared_ptr<Pyro::IndexBuffer> m_IndexBuffer;
		m_IndexBuffer.reset(Pyro::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));

		m_VertexArray->SetIndexBuffer(m_IndexBuffer);



		m_SquareVA.reset(Pyro::VertexArray::Create());

		float vertices2[4 * 3] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.5f,	0.5f, 0.0f,
			-0.5f,  0.5f, 0.0f
		};

		std::shared_ptr<Pyro::VertexBuffer> squareVB;
		squareVB.reset(Pyro::VertexBuffer::Create(vertices2, sizeof(vertices2)));


		squareVB->SetLayout({
				{ Pyro::ShaderDataType::Float3, "a_Position"}
			});
		m_SquareVA->AddVertexBuffer(squareVB);

		uint32_t indices2[3 * 2] = {
			0, 1, 2,
			2, 3, 0
		};

		std::shared_ptr<Pyro::IndexBuffer> squareIB;
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
		if(Pyro::Input::IsKeyPressed(PY_KEY_LEFT))
			m_CameraPosition.x -= m_CameraMoveSpeed * ts;
		else if (Pyro::Input::IsKeyPressed(PY_KEY_RIGHT))
			m_CameraPosition.x += m_CameraMoveSpeed * ts;

		if (Pyro::Input::IsKeyPressed(PY_KEY_UP))
			m_CameraPosition.y += m_CameraMoveSpeed * ts;
		else if (Pyro::Input::IsKeyPressed(PY_KEY_DOWN))
			m_CameraPosition.y -= m_CameraMoveSpeed * ts;



		if (Pyro::Input::IsKeyPressed(PY_KEY_A))
			m_CameraRotation += m_CameraRotationSpeed * ts;
		else if (Pyro::Input::IsKeyPressed(PY_KEY_D))
			m_CameraRotation -= m_CameraRotationSpeed * ts;



		if (Pyro::Input::IsKeyPressed(PY_KEY_J))
			m_SquarePos.x -= m_SquareMoveSpeed * ts;
		else if (Pyro::Input::IsKeyPressed(PY_KEY_L))
			m_SquarePos.x += m_SquareMoveSpeed * ts;

		if (Pyro::Input::IsKeyPressed(PY_KEY_I))
			m_SquarePos.y += m_SquareMoveSpeed * ts;
		else if (Pyro::Input::IsKeyPressed(PY_KEY_K))
			m_SquarePos.y -= m_SquareMoveSpeed * ts;



		Pyro::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Pyro::RenderCommand::Clear();

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);


		Pyro::Renderer::BeginScene(m_Camera);

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_SquarePos);

		Pyro::Renderer::Submit(m_SquareVA, m_Shader2, transform);
		Pyro::Renderer::Submit(m_VertexArray, m_Shader);

		Pyro::Renderer::EndScene();
	}

	void OnEvent(Pyro::Event& evnt) override
	{

	}

private:
	std::shared_ptr<Pyro::Shader> m_Shader;
	std::shared_ptr<Pyro::VertexArray> m_VertexArray;

	std::shared_ptr<Pyro::Shader> m_Shader2;
	std::shared_ptr<Pyro::VertexArray> m_SquareVA;

	Pyro::OrthographicCamera m_Camera;

	glm::vec3 m_CameraPosition;
	float m_CameraMoveSpeed = 4.0f;

	float m_CameraRotation = 0.0f;
	float m_CameraRotationSpeed = 45.0f;

	glm::vec3 m_SquarePos;
	float m_SquareMoveSpeed = 1.0f;
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