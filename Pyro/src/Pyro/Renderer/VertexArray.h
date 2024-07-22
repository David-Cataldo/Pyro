#pragma once

#include "Buffer.h"

namespace Pyro
{
	enum class MeshType
	{
		TRI = 0,
		QUAD = 1
	};


	class VertexArray
	{
	public:
		virtual ~VertexArray() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void AddVertexBuffer(Ref<VertexBuffer> vertexBuffer) = 0;
		virtual void SetIndexBuffer(Ref<IndexBuffer> indexBuffer) = 0;

		virtual void SetMeshType(MeshType type) = 0;
		virtual MeshType GetMeshType() = 0;

		virtual const std::vector<Ref<VertexBuffer>>& GetVertexBuffers() const = 0;
		virtual Ref<IndexBuffer> GetIndexBuffer() const = 0;

		static VertexArray* Create();
		static void CalcNormals(unsigned int* indices, unsigned int indiceCount, float* vertices, unsigned int verticeCount,
			unsigned int stride, unsigned int normalOffset);
	};
}