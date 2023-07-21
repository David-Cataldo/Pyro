#pragma once

#include <glm/glm.hpp>

#include "Pyro/Core/GameObject.h"

namespace Pyro
{
	class Camera : public GameObject
	{
	public:
		Camera() { m_Name = "Camera" + std::to_string(Increment<Camera>()); }
		virtual ~Camera() {}

		virtual glm::vec3 GetPosition() const = 0;
		virtual const glm::mat4& GetProjectionMatrix() const = 0;
		virtual const glm::mat4& GetViewMatrix() const = 0;
		virtual const glm::mat4& GetViewProjectionMatrix() const = 0;

	private:
		virtual void CalculateViewMatrix() = 0;
	};
}