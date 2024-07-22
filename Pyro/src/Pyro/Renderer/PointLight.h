#pragma once

#include "glm/glm.hpp"

#include "Light.h"

namespace Pyro
{
	struct LightData
	{
		glm::vec3 m_Pos;
		glm::vec3 m_Color;

		float m_ConstantAtt;
		float m_LinearAtt;
		float m_QuadraticAtt;

		float m_DiffuseIntensity;
		float m_SpecularIntensity;
	};


	class PointLight : public Light
	{
	public:
		PointLight();

		PointLight(glm::vec3 pos);

		PointLight(glm::vec3 pos, glm::vec3 col);

		PointLight(glm::vec3 pos, glm::vec3 col, float cA, float lA, float qA, float DI, float SI);

		Ref<LightData> GetLightData() { return m_Data; }

	private:
		Ref<LightData> m_Data;
	};
}