#include "pypch.h"
#include "Scene.h"

#include <glm/glm.hpp>

namespace Pyro
{
	Scene::Scene()
	{
		/*
		struct TransformComponent
		{
			glm::mat4 Transform;

			TransformComponent() = default;
			TransformComponent(const TransformComponent&) = default;
			TransformComponent(const glm::mat4 transform)
				: Transform(transform) {}

			operator glm::mat4& () { return Transform; }
			operator const glm::mat4&() { return Transform; }
		};

		struct MeshComponent
		{

		};

		entt::entity entity = m_Registry.create();
		m_Registry.emplace<TransformComponent>(entity, glm::mat4(1.0f));

		TransformComponent& transform = m_Registry.get<TransformComponent>(entity);

		auto view = m_Registry.view<TransformComponent>();

		for (auto entity : view)
		{

		}

		auto group = m_Registry.group<TransformComponent>(entt::get<MeshComponent>);
		*/
	}

	Scene::~Scene()
	{

	}
}
