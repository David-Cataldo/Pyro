#pragma once

#include "Core.h"

#include "Window.h"
#include "Pyro/LayerStack.h"
#include "Events/Event.h"
#include "Pyro/Events/ApplicationEvent.h"

#include "Pyro/Core/Timestep.h"

#include "ImGui/ImGuiLayer.h"

namespace Pyro
{
	class Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline float GetTimestep() { return m_Timestep; }

		inline static float GetFPS() { return Get().GetTimestep(); }

		inline static Application& Get() { return *s_Instance; }
		inline Window& GetWindow() { return *m_Window; }
	
	private:
		bool OnWindowClose(WindowCloseEvent& e);

	private:
		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;
		float m_LastFrameTime = 0.0f;
		Timestep m_Timestep;

	private:
		static Application* s_Instance;
	};

	// To be defined in CLIENT
	Application* CreateApplication();
}

