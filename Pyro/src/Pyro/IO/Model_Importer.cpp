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

			uint32_t* indices = new uint32_t[m.Indices.size()];
			std::copy(m.Indices.begin(), m.Indices.end(), indices);

			Ref<IndexBuffer> ib;
			ib.reset(IndexBuffer::Create(indices, sizeof(uint32_t) * m.Indices.size()));

			va->SetIndexBuffer(ib);

			float* vertices = new float[m.Vertices.size() * 5];
			int index = 0;
			for (objl::Vertex v : m.Vertices)
			{
				vertices[index] = v.Position.X;
				vertices[index+1] = v.Position.Y;
				vertices[index+2] = v.Position.Z;
				vertices[index+3] = v.TextureCoordinate.X;
				vertices[index+4] = v.TextureCoordinate.Y;

				index+=5;
			}

			Ref<VertexBuffer> vb;
			vb.reset(VertexBuffer::Create(vertices, sizeof(float) * m.Vertices.size() * 5));

			vb->SetLayout({
				{ Pyro::ShaderDataType::Float3, "a_Position"},
				{ Pyro::ShaderDataType::Float2, "a_TextureCoords"}
			});

			va->AddVertexBuffer(vb);

			curMesh->Create(va, Ref<Material>(new Material(shader, texture)));
			modelToBeSet->m_Meshes.push_back(curMesh);
		}
	
		

	
	}
}