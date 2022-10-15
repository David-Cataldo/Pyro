#include "pypch.h"
#include "ShaderParser.h"

namespace Pyro
{
	std::unordered_map<ShaderDataType, std::string> ShaderParser::ParseUniforms(std::string ShaderLoc, std::string uniformPrefix)
	{
		std::ifstream shader("shader.txt");
		std::unordered_map<ShaderDataType, std::string> uniforms;

		std::string currentLine;
		std::string curName;
		ShaderDataType curType;


		while (shader)
		{
			std::getline(shader, currentLine);

			if (currentLine.find(uniformPrefix) == std::string::npos || currentLine.find("uniform ") == std::string::npos)
				continue;

			int start = currentLine.find("uniform ") + 8;
			int middle = currentLine.find(" ", start);

			curName = currentLine.substr(middle + 1);
			curType = ShaderDataTypeFromString(currentLine.substr(start, middle - start));

			uniforms.insert({ curType, curName });

			shader.tellg();
		}
		return uniforms;
	}
}