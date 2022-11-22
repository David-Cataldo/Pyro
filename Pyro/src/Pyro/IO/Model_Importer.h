#pragma once

#include "../vendor/OBJ_loader/include/OBJ_Loader.h"

#include "Pyro/Renderer/Model.h"

namespace Pyro
{
	class Model_Importer
	{
	public:
		static void ImportAndSetModel(const std::string& fileLocation, Model* modelToBeSet);
	};
}	