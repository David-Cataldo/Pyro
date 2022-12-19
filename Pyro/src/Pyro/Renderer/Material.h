#pragma once

#include "Texture.h"
#include "Shader.h"

namespace Pyro
{
	class Material
	{
	public:
		Material(Ref<Shader> shader, Ref<Texture> texture)
			: m_Shader(shader), m_Texture(texture)
		{}

		Material(Ref<Shader> shader, const std::string& texLoc = "Assets/Textures/plain.png")
			: m_Shader(shader), m_Texture(Texture::Create(texLoc))
		{}

		Ref<Shader> GetShader() { return m_Shader; }
		Ref<Texture> GetTexture() { return m_Texture; }

	private:
		Ref<Shader> m_Shader;
		Ref<Texture> m_Texture;
	};
}