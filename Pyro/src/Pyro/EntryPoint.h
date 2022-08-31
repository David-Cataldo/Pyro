#pragma once

#ifdef PY_PLATFORM_WINDOWS

extern Pyro::Application* Pyro::CreateApplication();

int main(int argc, char** argv)
{
	Pyro::Log::Init();
	PY_CORE_WARN("Initialized Log!");
	PY_INFO("Hello!");

	auto app = Pyro::CreateApplication();
	app->Run();
	delete app;
}
	
#endif