#pragma once

#include <glm/glm.hpp>

namespace Pyro
{
	class Camera
	{
	public:
		virtual ~Camera() {}

		virtual const glm::mat4& GetProjectionMatrix() const = 0;
		virtual const glm::mat4& GetViewMatrix() const = 0;
		virtual const glm::mat4& GetViewProjectionMatrix() const = 0;

	private:
		virtual void CalculateViewMatrix() = 0;
	};
}