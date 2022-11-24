#include "pypch.h"
#include "Model_Importer.h"

namespace Pyro
{
	void Model_Importer::ImportAndSetModel(const std::string& fileLocation, Model* modelToBeSet)
	{
		Ref<Shader> shader;
		shader.reset(Shader::Create("Assets/Shaders/Test.vert.txt", "Assets/Shaders/Test.frag.txt"));

		objl::Loader loader;
		loader.LoadFile(fileLocation);

		for (objl::Mesh m : loader.LoadedMeshes)
		{
			Ref<Mesh> curMesh;
			curMesh.reset(new Mesh());

			modelToBeSet->SetTransform(glm::mat4(1.0f));

			Ref<Texture> texture;
			texture.reset(Texture::Create(m.MeshMaterial.map_Kd));

			Ref<VertexArray> va;
			va.reset(VertexArray::Create());

			

			//curMesh->Create(TEMPVA, Ref<Material>(new Material(shader, texture)));
		}
	
		

	
	}
}