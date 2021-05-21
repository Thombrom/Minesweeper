workspace "Minesweeper"
	architecture "x64"
	startproject "Minesweper"

	configurations
	{
		"Debug",
		"Release"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Minesweeper"
	location "src"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"src/**.h",
		"src/**.cpp",
		"vendor/glad/src/**.c"
	}

	libdirs 
	{
		"vendor/glfw/lib",
		"vendor/freetype/lib"
	}

	links {
		"opengl32",
		"glfw3",
		"freetyped"
	}

	includedirs
	{
		"src",
		"vendor/glfw",
		"vendor/glad/include",
		"vendor/freetype/include",
		"vendor/glm/include"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"MINESWEEPER_PLATFORM_WINDOWS"
		}

		filter "configurations:Debug"
			defines "MINESWEEPER_DEBUG"
			symbols "On"
			staticruntime  "default"
	
		filter "configurations:Release"
			defines "MINESWEEPER_RELEASE"
			optimize "On"
			staticruntime  "default"