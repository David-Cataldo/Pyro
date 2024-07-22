#pragma once

#include <queue>

#include "PhysicsComponent.h"
#include "Pyro/Core/Timestep.h"

namespace Pyro
{
	class PhysicsEngine
	{
	public:
		static void Submit(Ref<PhysicsComponent> comp);
		static void UpdatePhysics(Timestep ts);
		
	private:
		static glm::vec3 s_gravStrength;
		static std::queue<Ref<PhysicsComponent>> s_Components;
	};
}