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
	location "Minesweeper"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"src/**.h",
		"src/**.cpp"
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
	
	filter "configurations:Release"
		defines "MINESWEEPER_RELEASE"
		optimize "On"