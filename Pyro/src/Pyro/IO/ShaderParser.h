#pragma once

#include "Pyro/Renderer/Buffer.h"

namespace Pyro
{
	class ShaderParser
	{
		static std::unordered_map<ShaderDataType, std::string> ParseUniforms(std::string ShaderLoc, std::string uniformPrefix);
	};
}