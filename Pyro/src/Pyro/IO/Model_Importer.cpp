#include "pypch.h"
#include "Model_Importer.h"

namespace Pyro
{
	void Model_Importer::ImportAndSetModel(const std::string& fileLocation, Mesh* modelToBeSet)
	{
		modelToBeSet->SetTransform(new TransformComponent(glm::mat4(1.0f)));

		objl::Loader loader;
		loader.LoadFile(fileLocation);

		Ref<Shader> shader;
		shader.reset(Shader::Create("Assets/Shaders/Test.vert.txt", "Assets/Shaders/Test.frag.txt"));
		Ref<Texture> texture;
		texture.reset(Texture::Create(""));

		modelToBeSet->SetMat(new Material(shader, texture));

	
	}
}