#pragma once

namespace Pyro
{
	class CubeMap
	{
	public:
		virtual ~CubeMap() {}

		static CubeMap* Create(const std::vector<std::string>& texLocs);

		virtual bool LoadTexture() = 0;
		virtual bool LoadTextureAlpha() = 0;

		virtual void Bind() = 0;
		virtual void Unbind() = 0;
		virtual void ClearTexture() = 0;

	};
}