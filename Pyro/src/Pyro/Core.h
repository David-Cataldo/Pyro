#pragma once

#ifdef PY_PLATFORM_WINDOWS
	#ifdef PY_BUILD_DLL
		#define PYRO_API __declspec(dllexport)
	#else
		#define PYRO_API __declspec(dllimport)
	#endif
#else
	#error Pyro only supports Windows!
#endif