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
	kind "SharedLib"
	language "C++"
	staticruntime "Off"

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

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		defines
		{
			"PY_PLATFORM_WINDOWS",
			"PY_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .. "/Sandbox/\"")
		}

	filter "configurations:Debug"
		defines "PY_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "PY_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "PY_DIST"
		runtime "Release"
		optimize "On"


project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	staticruntime "Off"

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
		"%{IncludeDir.glm}"
	}

	links
	{
		"Pyro"
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		defines
		{
			"PY_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "PY_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "PY_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "PY_DIST"
		runtime "Release"
		optimize "On"