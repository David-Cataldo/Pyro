#pragma once

#include <vector>

#include "Pyro/Layer.h"

#include "Pyro/Events/ApplicationEvent.h"
#include "Pyro/Events/KeyEvent.h"
#include "Pyro/Events/MouseEvent.h"

#include "ImGUIComponent.h"


namespace Pyro
{
	class PYRO_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();
		
		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;
		virtual void OnEvent(Event& evnt) override;

		void AddComponent(Ref<ImGUIComponent> comp) { m_Components.push_back(comp); }

		void Begin();
		void End();

	private:
		std::vector<Ref<ImGUIComponent>> m_Components;
	};
}