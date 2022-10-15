#pragma once

#include "OBJ_Loader.h"

#include "Pyro/Renderer/Model.h"

namespace Pyro
{
	class Model_Importer
	{
	public:
		void ImportAndSetModel(const std::string& fileLocation, Model& modelToBeSet);
	};
}