#include "pypch.h"
#include "Skybox.h"

namespace Pyro
{

	Skybox::Skybox()
	{
	}

	Skybox::Skybox(std::vector<std::string> texLocs)
	{
		Ref<Shader> shader;
		shader.reset(Shader::Create("Assets/Shaders/Skybox.vert.txt", "Assets/Shaders/Skybox.frag.txt"));

		uint32_t skyboxIndices[] = {
			// front
			0, 1, 2,
			2, 1, 3,
			// right
			2, 3, 5,
			5, 3, 7,
			// back
			5, 7, 4,
			4, 7, 6,
			// left
			4, 6, 0,
			0, 6, 1,
			// top
			4, 0, 5,
			5, 0, 2,
			// bottom
			1, 6, 3,
			3, 6, 7
		};

		float skyboxVertices[] = {
			-1.0f, 1.0f, -1.0f,		0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
			-1.0f, -1.0f, -1.0f,	0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
			1.0f, 1.0f, -1.0f,		0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
			1.0f, -1.0f, -1.0f,		0.0f, 0.0f,		0.0f, 0.0f, 0.0f,

			-1.0f, 1.0f, 1.0f,		0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
			1.0f, 1.0f, 1.0f,		0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
			-1.0f, -1.0f, 1.0f,		0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
			1.0f, -1.0f, 1.0f,		0.0f, 0.0f,		0.0f, 0.0f, 0.0f
		};


	}

	Skybox::Skybox(std::string texLoc)
	{
	}

	void Skybox::DrawSkybox(glm::mat4 viewMatrix, glm::mat4 projMatrix)
	{
		
	}

	Skybox::~Skybox()
	{
	}
}
