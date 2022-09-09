workspace "Pyro"
	architecture "x64"
	startproject "Sandbox"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "Pyro/vendor/GLFW/include"
IncludeDir["Glad"] = "Pyro/vendor/Glad/include"
IncludeDir["ImGui"] = "Pyro/vendor/imgui"
IncludeDir["glm"] = "Pyro/vendor/glm"

group "Dependencies"
	include "Pyro/vendor/GLFW"
	include "Pyro/vendor/Glad"
	include "Pyro/vendor/imgui"

 group ""

project "Pyro"
	location "Pyro"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "pypch.h"
	pchsource "Pyro/src/pypch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl"
	}

	includedirs 
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}"
	}

	links
	{
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"PY_PLATFORM_WINDOWS",
			"PY_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

	filter "configurations:Debug"
		defines "PY_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "PY_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "PY_DIST"
		runtime "Release"
		optimize "on"


project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs 
	{
		"Pyro/vendor/spdlog/include",
		"Pyro/src",
		"Pyro/vendor",
		"%{IncludeDir.glm}"
	}

	links
	{
		"Pyro"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"PY_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "PY_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "PY_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "PY_DIST"
		runtime "Release"
		optimize "on"