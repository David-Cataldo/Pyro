#include "pypch.h"
#include "Model.h"

#define TINYOBJLOADER_IMPLEMENTATION

#include "../IO/tiny_obj_loader.h"



namespace Pyro
{
	Model::Model(std::string objLoc)
		: m_Meshes(std::vector<Ref<Mesh>>()), m_Transform(new TransformComponent(glm::mat4()))
	{
        m_Transform->Transform = glm::scale(m_Transform->Transform, glm::vec3(.0100, .0100, .0100));
        /*
        std::cout << "2" << std::endl;

		m_Transform.reset(new TransformComponent(glm::mat4(1.0f)));
		Ref<Shader> shader;

		shader.reset(Shader::Create("Assets/Shaders/Test.vert.txt", "Assets/Shaders/Test.frag.txt"));

        std::vector<std::vector<float>> vertices;
        std::vector<std::vector<uint32_t>> indices;
        std::vector<Ref<Material>> mats;

        // FROM TINYOBJLOADER WEBSITE
        tinyobj::ObjReaderConfig reader_config;
        reader_config.mtl_search_path = "Assets/Textures";

        tinyobj::ObjReader reader;

        if (!reader.ParseFromFile(objLoc, reader_config))
            if (!reader.Error().empty())
                PY_ERROR("TinyObjReader: " + reader.Error());

        if (!reader.Warning().empty())
            PY_WARN("TinyObjReader: " + reader.Warning());

        auto& attrib = reader.GetAttrib();
        auto& shapes = reader.GetShapes();
        auto& materials = reader.GetMaterials();

        std::cout << "3" << std::endl;

        // Loop over shapes
        for (size_t s = 0; s < shapes.size(); s++) {
            // Loop over faces(polygon)

            vertices.push_back(std::vector<float>());
            indices.push_back(std::vector<uint32_t>());

            size_t index_offset = 0;
            for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++) {
                size_t fv = size_t(shapes[s].mesh.num_face_vertices[f]);

                // Loop over vertices in the face.
                for (size_t v = 0; v < fv; v++) {
                    // access to vertex
                    tinyobj::index_t idx = shapes[s].mesh.indices[index_offset + v];
                    vertices[s].push_back(attrib.vertices[3 * size_t(idx.vertex_index) + 0]);
                    vertices[s].push_back(attrib.vertices[3 * size_t(idx.vertex_index) + 1]);
                    vertices[s].push_back(attrib.vertices[3 * size_t(idx.vertex_index) + 2]);

                    // Check if `normal_index` is zero or positive. negative = no normal data
                    if (idx.normal_index >= 0) {
                        tinyobj::real_t nx = attrib.normals[3 * size_t(idx.normal_index) + 0];
                        tinyobj::real_t ny = attrib.normals[3 * size_t(idx.normal_index) + 1];
                        tinyobj::real_t nz = attrib.normals[3 * size_t(idx.normal_index) + 2];
                    }

                    // Check if `texcoord_index` is zero or positive. negative = no texcoord data
                    if (idx.texcoord_index >= 0) {
                        vertices[s].push_back(attrib.texcoords[2 * size_t(idx.texcoord_index) + 0]);
                        vertices[s].push_back(attrib.texcoords[2 * size_t(idx.texcoord_index) + 1]);
                    }
                    else
                    {
                        vertices[s].push_back(0);
                        vertices[s].push_back(0);
                    }
                    indices[s].push_back(fv + index_offset);
                }
                index_offset += fv;

                // per-face material
                if (mats.size() <= s)
                {
                    mats.push_back(Ref<Material>());
                    mats[f].reset(new Material(shader, materials[shapes[s].mesh.material_ids[f]].diffuse_texname));
                }
                
            }
        }

        std::cout << "4" << std::endl;

        std::vector<Ref<VertexBuffer>> vbs;
        std::vector<Ref<IndexBuffer>> ibs;
        std::vector<Ref<VertexArray>> vas;

        std::cout << "5" << std::endl;

        for (int i = 0; i < vertices.size(); i++)
        {
            std::cout << "6" << std::endl;

            // Setting vertex buffers
            vbs.push_back(Ref<VertexBuffer>());
            vbs[i].reset(VertexBuffer::Create(&(vertices[i][0]), sizeof(float) * vertices[i].size()));
            std::cout << "7" << std::endl;

            vbs[i]->SetLayout({
                { Pyro::ShaderDataType::Float3, "a_Position"},
                { Pyro::ShaderDataType::Float2, "a_TextureCoords"}
            });
            std::cout << "8" << std::endl;

            // Setting index buffers
            ibs.push_back(Ref<IndexBuffer>());
            ibs[i].reset(IndexBuffer::Create(&(indices[i][0]), sizeof(uint32_t) * indices[i].size()));
            std::cout << "9" << std::endl;

            vas.push_back(Ref<VertexArray>());
            vas[i].reset(VertexArray::Create());
            vas[i]->AddVertexBuffer(vbs[i]);
            vas[i]->SetIndexBuffer(ibs[i]);
            std::cout << "10" << std::endl;

            m_Meshes.push_back(Ref<Mesh>());
            std::cout << "11" << std::endl;

            m_Meshes[i]->Create(vas[i], mats[i]);
            std::cout << "15" << std::endl;

            m_Meshes[i]->GetMat();
            std::cout << "16" << std::endl;


        }
        std::cout << "17" << std::endl;

        */

        tinyobj::ObjReader reader;
        tinyobj::ObjReaderConfig config;
        std::string err;
        bool success = reader.ParseFromFile(objLoc, config);
        
        if (!success) {
            std::cerr << "Failed to load model.obj: " << err << std::endl;
            return;
        }
        
        // Create an array of vertices
        std::vector<float> vertices;
        for (const auto& shape : reader.GetShapes()) {
            for (const auto& index : shape.mesh.indices) {
                // Get the position of the vertex
                const float x = reader.GetAttrib().vertices[3 * index.vertex_index + 0];
                const float y = reader.GetAttrib().vertices[3 * index.vertex_index + 1];
                const float z = reader.GetAttrib().vertices[3 * index.vertex_index + 2];
                // Add the vertex to the array
                vertices.push_back(x);
                vertices.push_back(y);
                vertices.push_back(z);
            }
        }
        
        // Create an array of indices
        std::vector<unsigned int> indices;
        for (const auto& shape : reader.GetShapes()) {
            for (const auto& index : shape.mesh.indices) {
                indices.push_back(index.vertex_index);
            }
        }
        
        // Create an array of diffuse texture names
        std::vector<std::string> diffuse_textures;
        for (const auto& material : reader.GetMaterials()) {
            diffuse_textures.push_back(material.diffuse_texname);
        }

        std::cout << vertices.size() << std::endl;
        std::cout << indices.size() << std::endl;
        std::cout << diffuse_textures.size();

        Ref<VertexArray> va;
        va.reset(VertexArray::Create());

        Ref<VertexBuffer> vb;
        vb.reset(Pyro::VertexBuffer::Create(vertices, sizeof(float) * vertices.size()));


        vb->SetLayout({
                { Pyro::ShaderDataType::Float3, "a_Position"},
                { Pyro::ShaderDataType::Float2, "a_TextureCoords"}
            });
        va->AddVertexBuffer(vb);

        Pyro::Ref<Pyro::IndexBuffer> ib;
        ib.reset(Pyro::IndexBuffer::Create(indices, sizeof(uint32_t) * indices.size()));

        va->SetIndexBuffer(ib);

        Ref<Texture> tex;
        tex.reset(Pyro::Texture::Create("Assets/Textures/plain.png"));

        Ref<Shader> shader;
        shader.reset(Shader::Create("Assets/Shaders/Test.vert.txt", "Assets/Shaders/Test.frag.txt"));

        Ref<Material> mat;
        mat.reset(new Material(shader, tex));

        Ref<Mesh> mesh;
        mesh.reset(new Mesh());
        mesh->Create(va, mat);
        mesh->GetMat()->GetTexture()->LoadTexture();

        m_Meshes.push_back(mesh);
	}

	Ref<Mesh> Model::operator[](int index)
	{
		return m_Meshes[index];
	}
}