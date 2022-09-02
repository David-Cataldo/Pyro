#include <Pyro.h>

class ExampleLayer : public Pyro::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{
	}

	void OnUpdate() override
	{
		//PY_INFO("ExampleLayer::Update");
	}

	void OnEvent(Pyro::Event& evnt) override
	{
		if (evnt.GetEventType() == Pyro::EventType::KeyPressed)
		{
			Pyro::KeyPressedEvent& e = (Pyro::KeyPressedEvent&)evnt;
			PY_TRACE("{0}", (char)e.GetKeyCode());
		}
	}
};

class Sandbox : public Pyro::Application
{
public:
	Sandbox() 
	{
		PushLayer(new ExampleLayer());
		PushOverlay(new Pyro::ImGuiLayer());
	}

	~Sandbox() {}
};


Pyro::Application* Pyro::CreateApplication()
{
	return new Sandbox();
}