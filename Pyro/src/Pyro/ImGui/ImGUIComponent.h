#pragma once

#include <string>

namespace Pyro
{
	class ImGUIComponent
	{
	public:
		static ImGUIComponent* CreateSlider(std::string name, float& initialValue, float min, float max);
		virtual void OnImGuiRender() = 0;
		
	protected:
		std::string m_Name;
	};
}