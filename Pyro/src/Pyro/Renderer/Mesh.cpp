#include "pypch.h"
#include "Mesh.h"


namespace Pyro
{
	void Mesh::Create(Ref<VertexArray> va, Ref<Material> mat)
	{ 
		m_VertexArray = va;

		m_Material = mat; 
	}
}