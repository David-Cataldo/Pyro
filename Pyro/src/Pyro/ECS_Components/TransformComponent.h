#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_access.hpp>

namespace Pyro
{
	struct TransformComponent
	{
		glm::mat4 Transform = glm::mat4(1.0f);
		glm::vec3 Position;

		TransformComponent() = default;
		TransformComponent(const TransformComponent&) = default;
		TransformComponent(const glm::mat4& transform)
			: Transform(transform) 
		{
			Position.x = transform[3][0];
			Position.y = transform[3][1];
			Position.z = transform[3][2];
		}

		void Translate(const glm::vec3& change) { Position += change; CalcModelMatrix(); }
		void CalcModelMatrix() { Transform = glm::translate(glm::mat4(1.0f), Position); }

		operator glm::mat4& () { return Transform; }
	};
}