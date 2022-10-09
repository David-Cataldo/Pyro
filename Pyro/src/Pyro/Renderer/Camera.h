#pragma once

#include <glm/glm.hpp>

namespace Pyro
{
	class Camera
	{
	public:
		virtual ~Camera() {}

		virtual void SetPosition(const glm::vec3& pos) = 0;
		virtual const glm::vec3& GetPosition() const = 0;

		virtual const glm::mat4& GetProjectionMatrix() const = 0;
		virtual const glm::mat4& GetViewMatrix() const = 0;
		virtual const glm::mat4& GetViewProjectionMatrix() const = 0;

	private:
		virtual void CalculateViewMatrix() = 0;
	};
}