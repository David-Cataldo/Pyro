#include "pypch.h"
#include "ImGUISlider.h"
#include "ImGuiBuild.cpp"

#include "backends/imgui_impl_opengl3.h"
#include "backends/imgui_impl_glfw.h"

namespace Pyro
{
	void ImGUISlider::OnImGuiRender()
	{
		ImGui::SliderFloat(m_Name.c_str(), &m_Value, m_Min, m_Max);
	}
}
