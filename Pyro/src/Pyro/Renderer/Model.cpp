#include "pypch.h"
#include "Model.h"

#include "Pyro/IO/OBJ_Loader.h"

#define TINYOBJLOADER_IMPLEMENTATION

#include "../IO/tiny_obj_loader.h"



namespace Pyro
{

	Model::Model(std::string objLoc)
		: m_Meshes(std::vector<Ref<Mesh>>()), m_Transform(new TransformComponent(glm::mat4()))
	{
		std::vector<Vertex> verts;
		std::vector<uint32_t> indices;
		std::string texLoc;
		std::string matLib;
		OBJLoader::LoadModel(objLoc, verts, indices, texLoc, matLib);

		std::vector<float> position;
		std::vector<float> norms;
		std::vector<float> tex;

		
		for (Vertex v : verts)
		{
			position.push_back(v.position.x);
			position.push_back(v.position.y);
			position.push_back(v.position.z);

			norms.push_back(v.normal.x);
			norms.push_back(v.normal.y);
			norms.push_back(v.normal.z);

			tex.push_back(v.texCoord.x);
			tex.push_back(v.texCoord.y);

			//std::cout << "Pos: (" << v.position.x << ", " << v.position.y << ", " << v.position.z << ")" << std::endl;
			//std::cout << "Norm: (" << v.normal.x << ", " << v.normal.y << ", " << v.normal.z << ")" << std::endl;
			//std::cout << "Tex: (" << v.texCoord.x << ", " << v.texCoord.y << ")" << std::endl;
		}

		for (uint32_t ind : indices)
		{
			//std::cout << ind << ", ";
		}



		Pyro::Ref<Pyro::VertexArray> m_SquareVA;
		Pyro::Ref<Pyro::Material> m_Mat;
		Pyro::Ref<Pyro::Mesh> m_Mesh;

		m_SquareVA.reset(Pyro::VertexArray::Create());




		Pyro::Ref<Pyro::VertexBuffer> squareVB;
		squareVB.reset(Pyro::VertexBuffer::Create(position, sizeof(float)*position.size()));


		squareVB->SetLayout({
				{ Pyro::ShaderDataType::Float3, "a_Position"}
			});

		Pyro::Ref<Pyro::VertexBuffer> squareVB1;
		squareVB1.reset(Pyro::VertexBuffer::Create(norms, sizeof(float)*norms.size()));


		squareVB1->SetLayout({
				{ Pyro::ShaderDataType::Float3, "a_Normal"}
			});

		Pyro::Ref<Pyro::VertexBuffer> squareVB2;
		squareVB2.reset(Pyro::VertexBuffer::Create(tex, sizeof(float)*tex.size()));


		squareVB2->SetLayout({
				{ Pyro::ShaderDataType::Float2, "a_TextureCoords"}
			});



		m_SquareVA->AddVertexBuffer(squareVB);
		m_SquareVA->AddVertexBuffer(squareVB2);
		m_SquareVA->AddVertexBuffer(squareVB1);


		Pyro::Ref<Pyro::IndexBuffer> squareIB;
		squareIB.reset(Pyro::IndexBuffer::Create(indices, sizeof(uint32_t)*indices.size()));

		m_SquareVA->SetIndexBuffer(squareIB);


		Pyro::Ref<Pyro::Shader> m_Shader2;
		m_Shader2.reset(Pyro::Shader::Create("Assets/Shaders/Test.vert.txt", "Assets/Shaders/PBR.frag.txt"));
		m_Transform.reset(new Pyro::TransformComponent(glm::mat4(1.0f)));

		Pyro::Ref<Pyro::Texture> m_Tex;
		m_Tex.reset(Pyro::Texture::Create("Assets/Textures/green.png"));

		m_Mat.reset(new Pyro::Material(m_Shader2, m_Tex, 0.1, 0.1, 0.0));

		m_Mesh.reset(new Pyro::Mesh());
		m_Mesh->Create(m_SquareVA, m_Mat);
		m_Mesh->GetMat()->GetTexture()->LoadTexture();
		
		m_Meshes.push_back(m_Mesh);
	}

	Ref<Mesh> Model::operator[](int index)
	{
		return m_Meshes[index];
	}
}