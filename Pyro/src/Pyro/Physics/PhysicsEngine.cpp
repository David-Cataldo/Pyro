#include "pypch.h"
#include "PhysicsEngine.h"

namespace Pyro
{
	glm::vec3 PhysicsEngine::s_gravStrength = glm::vec3(0.0f, -9.81f, 0.0f);
	std::queue<Ref<PhysicsComponent>> PhysicsEngine::s_Components;

	void PhysicsEngine::Submit(Ref<PhysicsComponent> comp)
	{
		s_Components.push(comp);
	}
	void PhysicsEngine::UpdatePhysics(Timestep ts)
	{
		while (!s_Components.empty())
		{
			Ref<PhysicsComponent> comp = s_Components.front();
			if(comp->m_gravEnabled)
				comp->m_Velocity += s_gravStrength * ts.GetSeconds();
			comp->m_Velocity += comp->m_NetForce / comp->m_Mass * ts.GetSeconds();
			*(comp->m_Position) += comp->m_Velocity * ts.GetSeconds();
			comp->m_NetForce = glm::vec3(0.0f);
			s_Components.pop();
		}
	}
}