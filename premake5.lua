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
IncludeDir["entt"] = "Pyro/vendor/entt/include"
IncludeDir["OBJ_loader"] = "Pyro/vendor/OBJ_loader/include"
IncludeDir["STBI"] = "Pyro/vendor/stbi/include"

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
		"%{prj.name}/vendor/glm/glm/**.inl",
		"%{prj.name}/vendor/stbi/include/stb_image.h",
		"%{prj.name}/vendor/OBJ_loader/include/OBJ_loader.h"
	}

	includedirs 
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.entt}",
		"%{IncludeDir.OBJ_loader}",
		"%{IncludeDir.STBI}"
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
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/stbi/include/stb_image.h",
		"%{prj.name}/vendor/OBJ_loader/include/OBJ_loader.h"
	}

	includedirs 
	{
		"Pyro/vendor/spdlog/include",
		"Pyro/src",
		"Pyro/vendor",
		"%{IncludeDir.glm}",
		"%{IncludeDir.entt}",
		"%{IncludeDir.OBJ_loader}",
		"%{IncludeDir.STBI}"
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