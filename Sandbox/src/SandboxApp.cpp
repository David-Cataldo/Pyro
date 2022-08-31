#include <Pyro.h>
#include <iostream>

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
		//PY_TRACE("{0}", evnt);
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