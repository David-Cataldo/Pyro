#pragma once

#ifdef PY_PLATFORM_WINDOWS

extern Pyro::Application* Pyro::CreateApplication();

int main(int argc, char** argv)
{
	auto app = Pyro::CreateApplication();
	app->Run();
	delete app;
}
	
#endif