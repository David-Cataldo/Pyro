#pragma once

#include "ImGUIComponent.h"

namespace Pyro
{
	class ImGUISlider : public ImGUIComponent
	{
	public:
		ImGUISlider(std::string name, float& initialValue, float min, float max)
			: m_Value(initialValue), m_Min(min), m_Max(max)
		{
			m_Name = name;
		}

		virtual void OnImGuiRender() override;

		float GetValue() { return m_Value; } const
		void SetValue(float& val) { m_Value = val; }

	private:
		float& m_Value;
		float m_Max;
		float m_Min;
	};
}