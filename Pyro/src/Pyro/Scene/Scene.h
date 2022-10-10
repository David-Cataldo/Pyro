#pragma once

#include "entt.hpp"

namespace Pyro
{
	class Scene
	{
	public:
		Scene();
		~Scene();

	private:
		entt::registry m_Registry;
	};
}