#include "pypch.h"
#include "Mesh.h"

#include "Pyro/IO/Model_Importer.h"

namespace Pyro
{
	void Mesh::Create(const Ref<VertexArray>& va, const Ref<Material>& mat, const Ref<TransformComponent>& tc)
	{ 
		m_VertexArray = va;
		m_Material = mat; 
		m_Transform = tc;
	}

	void Mesh::CreateFromOBJFile(const std::string& fileLoc)
	{ 
		Model_Importer::ImportAndSetModel(fileLoc, this);
	}


}