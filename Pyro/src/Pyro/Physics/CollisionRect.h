#pragma once

#include "CollisionBox.h"

namespace Pyro
{
	class CollisionRect : public CollisionBox
	{
	public:
		CollisionRect();
		CollisionRect(float dim, Ref<glm::vec3> pos);
		CollisionRect(const glm::vec3& dims, Ref<glm::vec3> pos);

		virtual ~CollisionRect() override;


	private:
		glm::vec3 m_RectDims;
	};
}