#pragma once

namespace Pyro
{
	class Texture
	{
	public:
		virtual ~Texture() {}

		static Texture* Create(const std::string& fileLoc);

		virtual bool LoadTexture() = 0;
		virtual bool LoadTextureAlpha() = 0;
		 
		virtual void Bind() = 0;
		virtual void Unbind() = 0;
		virtual void ClearTexture() = 0;

		static void LoadPlainTexture();
	};
}