#include "pypch.h"
#include "CollisionSphere.h"

namespace Pyro
{
	CollisionSphere::CollisionSphere()
		: m_Radius(1.0f)
	{
		m_Pos = Ref<glm::vec3>(new glm::vec3(0.0f));
		m_Type = ColliderType::Sphere;
	}

	CollisionSphere::CollisionSphere(float rad, Ref<glm::vec3> pos)
		: m_Radius(rad)
	{
		m_Pos = pos;
	}

	CollisionSphere::~CollisionSphere()
	{
	}
}