workspace "Minesweeper"
	architecture "x64"
	startproject "Minesweper"

	configurations
	{
		"Debug",
		"Release"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "vendor/glfw/include"

include "vendor/glfw"

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
		"vendor/glad/src/**.c",
        "vendor/stb/stb_image.cpp"
	}

	libdirs 
	{
		"vendor/glfw/lib",
		"vendor/freetype/lib"
	}

	links {
		"GLFW",
	}

	includedirs
	{
		"src",
		"vendor/glad/include",
		"vendor/freetype/include",
		"vendor/glm/include",
        "vendor/stb",
		"%{IncludeDir.GLFW}"
	}

	cppdialect "C++17"
	staticruntime "On"
	systemversion "latest"

	

	filter "configurations:Debug"
		defines "MINESWEEPER_DEBUG"
		symbols "On"
		staticruntime  "default"
	
	filter "configurations:Release"
		defines "MINESWEEPER_RELEASE"
		optimize "On"
		staticruntime  "default"

	filter "system:windows"
		defines
		{
			"MINESWEEPER_PLATFORM_WINDOWS"
		}

        links {
		    "freetyped",
            "opengl32"
        }

	filter "system:linux"
		defines
		{
			"MINESWEEPER_PLATFORM_LINUX"
		}

        links {
            "freetype",
            "dl",
            "pthread"
        }
		
