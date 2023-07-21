#include "pypch.h"
#include "ImGUIComponent.h"

#include "ImGUISlider.h"

namespace Pyro
{
	ImGUIComponent* ImGUIComponent::CreateSlider(std::string name, float& initialValue, float min, float max)
	{
		return new ImGUISlider(name, initialValue, min, max);
	}
}