#pragma once

#include <glm/glm.hpp>
#include <cmath>

namespace Pyro
{
	namespace Math
	{
		inline float Dist(const glm::vec2& one, const glm::vec2& two)
		{
			return sqrt(pow(abs(one.x - two.x), 2) + pow(abs(one.y - two.y), 2));
		}

		inline float Dist(const glm::vec3& one, const glm::vec3& two)
		{
			return cbrt(pow(abs(one.x - two.x), 3) + pow(abs(one.y - two.y), 3) + pow(abs(one.z - two.z), 3));
		}
	}
}