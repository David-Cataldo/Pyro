#include "pypch.h"
#include "PointLight.h"

namespace Pyro
{
	PointLight::PointLight() :
		m_Data(new LightData{ glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), 0.3f, 0.2f, 0.1f, 1.0f, 1.0f })
	{
	}

	PointLight::PointLight(glm::vec3 pos)
		: m_Data(new LightData{pos, glm::vec3(1.0f, 1.0f, 1.0f), 0.3f, 0.2f, 0.1f, 1.0f, 1.0f})
	{
	}

	PointLight::PointLight(glm::vec3 pos, glm::vec3 col)
		: m_Data(new LightData{pos, col, 0.3f, 0.2f, 0.1f, 1.0f, 1.0f})
	{
	}

	PointLight::PointLight(glm::vec3 pos, glm::vec3 col, float cA, float lA, float qA, float DI, float SI)
		: m_Data(new LightData{pos, col, cA, lA, qA, DI, SI})
	{
	}
}