#pragma once

#include "Pyro/Layer.h"

#include "Pyro/Events/ApplicationEvent.h"
#include "Pyro/Events/KeyEvent.h"
#include "Pyro/Events/MouseEvent.h"


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

		void Begin();
		void End();
	};
}