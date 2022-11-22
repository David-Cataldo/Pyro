#pragma once

#include "Texture.h"
#include "Shader.h"

namespace Pyro
{
	class Material
	{
	public:
		Material(const Ref<Shader>& shader, const Ref<Texture>& texture)
			: m_Shader(shader), m_Texture(texture)
		{}

		const Ref<Shader>& GetShader() { return m_Shader; }
		const Ref<Texture>& GetTexture() { return m_Texture; }

	private:
		Ref<Shader> m_Shader;
		Ref<Texture> m_Texture;
	};
}