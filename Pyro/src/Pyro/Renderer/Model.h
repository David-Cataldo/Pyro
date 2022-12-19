#pragma once

#include "Mesh.h"

namespace Pyro
{
	class Model
	{
	public:
		Model(std::string objLoc);

		Model(std::vector<Ref<Mesh>> mesh = std::vector<Ref<Mesh>>(), Ref<TransformComponent> trans = Ref<TransformComponent>(new TransformComponent(glm::mat4(1.0f))))
			: m_Meshes(mesh), m_Transform(trans)
		{}

		const std::vector<Ref<Mesh>>& GetMeshes() { return m_Meshes; }
		const Ref<TransformComponent>& GetTransform() { return m_Transform; }

		void SetTransform(Ref<TransformComponent> trans) { m_Transform = trans; }
		void SetTransform(const glm::mat4& mat) { m_Transform.reset(new TransformComponent(mat)); }
		
		Ref<Mesh> operator[] (int);

	private:
		std::vector<Ref<Mesh>> m_Meshes;
		Ref<TransformComponent> m_Transform;
	};
}