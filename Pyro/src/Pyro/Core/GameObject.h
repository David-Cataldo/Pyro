#pragma once

#include <string>
#include <map>

namespace Pyro
{
	class GameObject
	{
	public:
		GameObject() { s_ObjectList[this] = &m_Name; }

		template<typename T>
		static unsigned int Increment() { static unsigned int count = 1; return count++; }

		const std::string& GetName() { return m_Name; }

		virtual ~GameObject() { s_ObjectList.erase(this); }
		
	protected:
		std::string m_Name;

	private:
		static std::map<GameObject*, std::string*> s_ObjectList;
	};
}