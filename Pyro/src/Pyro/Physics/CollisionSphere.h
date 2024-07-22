#pragma once

#include "CollisionBox.h"

namespace Pyro
{
	class CollisionSphere : public CollisionBox
	{
	public:
		CollisionSphere();
		CollisionSphere(float rad, Ref<glm::vec3> pos);

		virtual ~CollisionSphere() override;


	private:
		float m_Radius;
	};
}