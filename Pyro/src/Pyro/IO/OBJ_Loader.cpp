#include "pypch.h"
#include "OBJ_Loader.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <glm/gtx/hash.hpp>

namespace Pyro
{

    bool Vertex::operator==(const Vertex& other) const
    {
        return position == other.position && texCoord == other.texCoord && normal == other.normal;
    }

    bool OBJLoader::LoadModel(const std::string& filePath, std::vector<Vertex>& vertices, std::vector<uint32_t>& indices, std::string& textureFileName, std::string& matlib)
    {
        std::ifstream file(filePath);
        if (!file.is_open())
        {
            std::cerr << "Failed to open OBJ file: " << filePath << std::endl;
            return false;
        }

        std::vector<glm::vec3> positions;
        std::vector<glm::vec2> texCoords;
        std::vector<glm::vec3> normals;

        std::unordered_map<Vertex, uint32_t, Hash> uniqueVertices;

        std::string line;
        while (std::getline(file, line))
        {
            std::istringstream iss(line);
            std::string prefix;
            iss >> prefix;

            if (prefix == "v")
            {
                glm::vec3 position;
                iss >> position.x >> position.y >> position.z;
                positions.push_back(position);
            }
            else if (prefix == "vt")
            {
                glm::vec2 texCoord;
                iss >> texCoord.x >> texCoord.y;
                texCoords.push_back(texCoord);
            }
            else if (prefix == "vn")
            {
                glm::vec3 normal;
                iss >> normal.x >> normal.y >> normal.z;
                normals.push_back(normal);
            }
            else if (prefix == "f")
            {
                std::vector<uint32_t> faceIndices;
                std::vector<uint32_t> texCoordIndices;
                std::vector<uint32_t> normalIndices;

                while (!iss.eof())
                {
                    std::string faceVertex;
                    iss >> faceVertex;

                    std::istringstream faceVertexStream(faceVertex);
                    std::string vertexIndexStr, texCoordIndexStr, normalIndexStr;
                    std::getline(faceVertexStream, vertexIndexStr, '/');
                    std::getline(faceVertexStream, texCoordIndexStr, '/');
                    std::getline(faceVertexStream, normalIndexStr, '/');

                    uint32_t vertexIndex = std::stoi(vertexIndexStr) - 1;
                    faceIndices.push_back(vertexIndex);

                    // Texture coordinates might not always be present in the OBJ file
                    if (!texCoordIndexStr.empty())
                    {
                        uint32_t texCoordIndex = std::stoi(texCoordIndexStr) - 1;
                        texCoordIndices.push_back(texCoordIndex);
                    }

                    uint32_t normalIndex = std::stoi(normalIndexStr) - 1;
                    normalIndices.push_back(normalIndex);
                }

                // Triangulate the face and add indices to the indices vector
                for (size_t i = 1; i < faceIndices.size() - 1; i++)
                {
                    indices.push_back(GetOrCreateIndex(faceIndices[0], texCoordIndices.empty() ? 0 : texCoordIndices[0], normalIndices[0], positions, texCoords, normals, vertices, uniqueVertices));
                    indices.push_back(GetOrCreateIndex(faceIndices[i], texCoordIndices.empty() ? 0 : texCoordIndices[i], normalIndices[i], positions, texCoords, normals, vertices, uniqueVertices));
                    indices.push_back(GetOrCreateIndex(faceIndices[i + 1], texCoordIndices.empty() ? 0 : texCoordIndices[i + 1], normalIndices[i + 1], positions, texCoords, normals, vertices, uniqueVertices));
                }
            }
            else if (prefix == "usemtl")
            {
                // Parse material name (texture file name)
                iss >> textureFileName;
            }
        }

        file.close();

        return true;
    }

    uint32_t OBJLoader::GetOrCreateIndex(uint32_t positionIndex, uint32_t texCoordIndex, uint32_t normalIndex,
        const std::vector<glm::vec3>& positions, const std::vector<glm::vec2>& texCoords,
        const std::vector<glm::vec3>& normals, std::vector<Vertex>& vertices,
        std::unordered_map<Vertex, uint32_t, Hash>& uniqueVertices)
    {
        Vertex vertex;
        vertex.position = positions[positionIndex];
        vertex.normal = normals[normalIndex];

        // Texture coordinates might not always be present in the OBJ file
        if (!texCoords.empty())
        {
            vertex.texCoord = texCoords[texCoordIndex];
        }
        else
        {
            vertex.texCoord = glm::vec2(0.0f); // If no texture coordinates are available, set to default value (0, 0)
        }

        auto it = uniqueVertices.find(vertex);
        if (it != uniqueVertices.end())
        {
            return it->second;
        }
        else
        {
            uint32_t newIndex = static_cast<uint32_t>(vertices.size());
            uniqueVertices[vertex] = newIndex;
            vertices.push_back(vertex);
            return newIndex;
        }
    }
}
