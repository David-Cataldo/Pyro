#pragma once

#include <vector>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtx/hash.hpp>
#include <functional>


namespace Pyro
{
    struct Vertex
    {
        glm::vec3 position;
        glm::vec2 texCoord;
        glm::vec3 normal;

        bool operator==(const Vertex& other) const;
    };

    class Hash {
    public:

        // Use sum of lengths of first and last names
        // as hash function.
        size_t operator()(const Vertex& v) const
        {
            std::size_t seed = 0;
            seed ^= std::hash<glm::vec3>()(v.position) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
            seed ^= std::hash<glm::vec2>()(v.texCoord) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
            seed ^= std::hash<glm::vec3>()(v.normal) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
            return seed;
        }
    };

    class OBJLoader
    {
    public:
        static bool LoadModel(const std::string& filePath, std::vector<Vertex>& vertices, std::vector<uint32_t>& indices, std::string& textureFileName, std::string& materialLib);
        static uint32_t GetOrCreateIndex(uint32_t positionIndex, uint32_t texCoordIndex, uint32_t normalIndex, const std::vector<glm::vec3>& positions, const std::vector<glm::vec2>& texCoords, const std::vector<glm::vec3>& normals, std::vector<Vertex>& vertices, std::unordered_map<Vertex, uint32_t, Hash>& uniqueVertices);
       // static std::string GetPathFromFilePath(const std::string& filePath);
    };
}