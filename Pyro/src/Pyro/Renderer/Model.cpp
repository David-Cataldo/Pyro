#include "pypch.h"
#include "Model.h"

namespace Pyro
{
	Ref<Mesh>& Model::operator[](int index)
	{
		return m_Meshes[index];
	}
}