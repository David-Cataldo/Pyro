#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_access.hpp>

namespace Pyro
{
	struct TransformComponent
	{
		glm::mat4 Transform = glm::mat4(1.0f);
		Ref<glm::vec3> Position;
		glm::vec3 OldPos;

		TransformComponent() = default;
		TransformComponent(const TransformComponent&) = default;
		TransformComponent(const glm::mat4& transform)
			: Transform(transform), Position(Ref<glm::vec3>(new glm::vec3(0.0f)))
		{
			Position->x = transform[3][0];
			Position->y = transform[3][1];
			Position->z = transform[3][2];
		}

		void CheckPosChange() 
		{ 
			if (Position->x != OldPos.x || Position->y != OldPos.y || Position->z != OldPos.z) 
			{ 
				OldPos = *Position; 
				CalcModelMatrix();
			}
		}

		void SetPos(glm::vec3 pos) { *Position = pos; }
		void Translate(glm::vec3 change) { *Position += change; }
		void CalcModelMatrix() { Transform = glm::translate(glm::mat4(1.0f), *Position); }

		operator glm::mat4& () { return Transform; }
	};
}