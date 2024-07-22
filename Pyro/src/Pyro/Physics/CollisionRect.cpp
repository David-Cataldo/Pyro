#include "pypch.h"

#include "CollisionRect.h"

namespace Pyro
{
	CollisionRect::CollisionRect()
		:m_RectDims(glm::vec3(1.0f))
	{
		m_Pos = Ref<glm::vec3>(new glm::vec3(0.0f));
		m_Type = ColliderType::Rect;
	}

	CollisionRect::CollisionRect(float dim, Ref<glm::vec3> pos)
		: m_RectDims(glm::vec3(dim))
	{
		m_Pos = pos;
	}

	CollisionRect::CollisionRect(const glm::vec3& dims, Ref < glm::vec3> pos)
		: m_RectDims(dims)
	{
		m_Pos = pos;
	}

	CollisionRect::~CollisionRect()
	{
	}
}