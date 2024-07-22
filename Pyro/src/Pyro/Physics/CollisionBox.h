#pragma once

#include "Pyro/Core.h"
#include "Pyro/Log.h"


namespace Pyro
{
	enum class ColliderType
	{
		Sphere,
		Rect
	};

	class CollisionBox
	{
	public:
		CollisionBox() {}
		virtual ~CollisionBox() {}

	protected:
		Ref<glm::vec3> m_Pos;
		ColliderType m_Type;
	};
}