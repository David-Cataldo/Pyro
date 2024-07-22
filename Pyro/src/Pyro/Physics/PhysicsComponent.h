#pragma once

#include "Pyro/Core.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_access.hpp>

#include "CollisionRect.h"
#include "CollisionSphere.h"


namespace Pyro
{
	struct PhysicsComponent
	{
		Ref<glm::vec3> m_Position;
		glm::vec3 m_Velocity;
		glm::vec3 m_NetForce;
		float m_Mass;
		bool m_gravEnabled = true;

		PhysicsComponent() = default;
		PhysicsComponent(const PhysicsComponent&) = default;
		PhysicsComponent(Ref<glm::vec3> pos, glm::vec3 vel = glm::vec3(0.0f), float mass = 1.0f, glm::vec3 force = glm::vec3(0.0f))
			: m_Position(pos), m_Velocity(vel),  m_Mass(mass), m_NetForce(force)
		{}

	};
}
