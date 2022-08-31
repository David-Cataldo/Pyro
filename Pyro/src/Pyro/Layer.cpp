#include "pypch.h"
#include "Layer.h"

namespace Pyro
{
	Layer::Layer(const std::string& debugName)
		: m_DebugName(debugName)
	{
	}

	Layer::~Layer()
	{
	}
}