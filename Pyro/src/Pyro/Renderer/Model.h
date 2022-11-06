#pragma once

#include "Pyro/Renderer/VertexArray.h"
#include "Pyro/Renderer/Material.h"
#include "Pyro/ECS_Components/TransformComponent.h"


namespace Pyro
{
	class Model
	{


	private:
		Ref<VertexArray> m_VertexArray;
		Material m_Material;
		TransformComponent m_Transform;
	};
}