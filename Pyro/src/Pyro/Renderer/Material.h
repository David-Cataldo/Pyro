#pragma once

#include "Texture.h"
#include "Shader.h"

namespace Pyro
{
	class Material
	{
	public:
		Material(Ref<Shader> shader, Ref<Texture> alb, float met, float rough, float ao)
			: m_Shader(shader), m_Albedo(alb), m_Metallic(met), m_Roughness(rough), m_AO(ao)
		{}

		Material(Ref<Shader> shader, Ref<Texture> texture)
			: m_Shader(shader), m_Albedo(texture), m_Roughness(0.1), m_Metallic(0.1), m_AO(0.1)
		{}

		Material(Ref<Shader> shader, const std::string& texLoc = "Assets/Textures/plain.png")
			: m_Shader(shader), m_Albedo(Texture::Create(texLoc)), m_Roughness(0.1), m_Metallic(0.1), m_AO(0.1)
		{}

		Ref<Shader> GetShader() { return m_Shader; }
		Ref<Texture> GetTexture() { return m_Albedo; }
		float& GetMetallic() { return m_Metallic; }
		float& GetRoughness() { return m_Roughness; }
		float& GetAO() { return m_AO; }

	private:
		Ref<Shader> m_Shader;

		Ref<Texture> m_Albedo;
		float m_Metallic;
		float m_Roughness;
		float m_AO;
	};
}