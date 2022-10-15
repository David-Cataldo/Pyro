#pragma once

#include "Pyro/Renderer/Mesh.h"
#include "Pyro/Renderer/Material.h"

namespace Pyro
{
	struct RenderableComponent
	{
		Mesh m_Mesh;
		Material m_Material;
	};
}