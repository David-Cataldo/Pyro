#pragma once

#include "Pyro/Core/GameObject.h"

#include "Mesh.h"
#include "Pyro/Physics/PhysicsComponent.h"

namespace Pyro
{
	class Model : public GameObject
	{
	public:
		Model(std::string objLoc);

		Model(std::vector<Ref<Mesh>> mesh = std::vector<Ref<Mesh>>(), Ref<TransformComponent> trans = Ref<TransformComponent>(new TransformComponent(glm::mat4(1.0f))), Ref<PhysicsComponent> phys = Ref<PhysicsComponent>(new PhysicsComponent()))
			: m_Meshes(mesh), m_Transform(trans)
		{
			m_PhysicComponent.reset(new PhysicsComponent(m_Transform->Position)); 
		}

		const std::vector<Ref<Mesh>>& GetMeshes() { return m_Meshes; }
		Ref<TransformComponent> GetTransform() { return m_Transform; }
		Ref<PhysicsComponent> GetPhys() { return m_PhysicComponent; }

		void SetTransform(Ref<TransformComponent> trans) { m_Transform = trans; }
		void SetTransform(const glm::mat4& mat) { m_Transform.reset(new TransformComponent(mat)); }
		
		Ref<Mesh> operator[] (int);

		virtual ~Model() override {  }

	private:
		std::vector<Ref<Mesh>> m_Meshes;
		Ref<TransformComponent> m_Transform;
		Ref<PhysicsComponent> m_PhysicComponent;
	};
}