#include "pypch.h"
#include "GameObject.h"

namespace Pyro
{
	std::map<GameObject*, std::string*> GameObject::s_ObjectList;
}