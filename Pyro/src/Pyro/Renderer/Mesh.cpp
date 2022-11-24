#include "pypch.h"
#include "Mesh.h"

#include "Pyro/IO/Model_Importer.h"

namespace Pyro
{
	void Mesh::Create(const Ref<VertexArray>& va, const Ref<Material>& mat)
	{ 
		m_VertexArray = va;
		m_Material = mat; 
	}

	void Mesh::CreateFromOBJFile(const std::string& fileLoc)
	{ 
		//Model_Importer::ImportAndSetModel(fileLoc, this);
	}


}