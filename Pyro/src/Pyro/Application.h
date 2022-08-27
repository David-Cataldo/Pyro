#pragma once

#include "Core.h"

namespace Pyro
{
	class PYRO_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	// To be defined in client
	Application* CreateApplication();
}

