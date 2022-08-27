#include <Pyro.h>

class Sandbox : public Pyro::Application
{
public:
	Sandbox() {}

	~Sandbox() {}
};


Pyro::Application* Pyro::CreateApplication()
{
	return new Sandbox();
}