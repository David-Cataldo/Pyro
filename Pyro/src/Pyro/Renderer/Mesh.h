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
			: m_VertexArray(nullptr), m_Material(nullptr)
		{}
		void Create(Ref<VertexArray> va, Ref<Material> mat); 

		Ref<VertexArray> GetVertexArray() { return m_VertexArray; }
		Ref<Material> GetMat() { return m_Material; }
		// TODO - CHANGE RAW POINTERS TO REFS
		void SetVertexArray(VertexArray* newVA) { m_VertexArray.reset(newVA); }
		void SetMat(Material* newMat) { m_Material.reset(newMat); }

	private:
		Ref<VertexArray> m_VertexArray;
		Ref<Material> m_Material;
	};
}