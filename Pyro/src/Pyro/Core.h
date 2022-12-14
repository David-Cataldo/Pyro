#pragma once

#ifdef PY_PLATFORM_WINDOWS
#if PY_DYNAMIC_LINK
	#ifdef PY_BUILD_DLL
		#define PYRO_API __declspec(dllexport)
	#else
		#define PYRO_API __declspec(dllimport)
	#endif
#else
	#define PYRO_API
#endif
#else
	#error Pyro only supports Windows!
#endif

#ifdef PY_DEBUG
	#define PY_ENABLE_ASSERTS
#endif

#ifdef PY_ENABLE_ASSERTS
	#define PY_ASSERT(x, ...) { if(!(x)) { PY_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define PY_CORE_ASSERT(x, ...) { if(!(x)) { PY_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }

#else
	#define PY_ASSERT(x, ...)
	#define PY_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#define PY_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)