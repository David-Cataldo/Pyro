#pragma once

#include "Model.h"
#include "Shader.h"
#include "Pyro/Core.h"

namespace Pyro
{

	class Skybox
	{
	public:
		Skybox();
		Skybox(std::vector<std::string> texLocs);
		Skybox(std::string texLoc);

		void DrawSkybox(glm::mat4 viewMatrix, glm::mat4 projMatrix);

		~Skybox();

	private:
		Ref<Model> m_Skybox;
	};
}