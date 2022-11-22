#pragma once

#include "Pyro/Renderer/VertexArray.h"
#include "Pyro/Renderer/Material.h"
#include "Pyro/ECS_Components/TransformComponent.h"

namespace Pyro
{
	class Mesh
	{
	public:
		Mesh() 
			: m_VertexArray(nullptr), m_Material(nullptr), m_Transform(nullptr)
		{}
		void Create(const Ref<VertexArray>& va, const Ref<Material>& mat, const Ref<TransformComponent>& tc); 
		void CreateFromOBJFile(const std::string& fileLoc); 

		Ref<VertexArray> GetVertexArray() { return m_VertexArray; }
		Ref<Material> GetMat() { return m_Material; }
		Ref<TransformComponent> GetTransform() { return m_Transform; }

		void SetVertexArray(VertexArray* newVA) { m_VertexArray.reset(newVA); }
		void SetMat(Material* newMat) { m_Material.reset(newMat); }
		void SetTransform(TransformComponent* newTrans) { m_Transform.reset(newTrans); }

	private:
		Ref<VertexArray> m_VertexArray;
		Ref<Material> m_Material;
		Ref<TransformComponent> m_Transform;
	};
}