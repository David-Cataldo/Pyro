#pragma once

#include "Mesh.h"

namespace Pyro
{
	class Model
	{
	public:
		Model(std::vector<Ref<Mesh>> mesh = std::vector<Ref<Mesh>>())
			: m_Meshes(mesh)
		{}

		const std::vector<Ref<Mesh>>& GetMeshes() { return m_Meshes; }
		
		Ref<Mesh>& operator[] (int);


	private:
		std::vector<Ref<Mesh>> m_Meshes;
	};
}