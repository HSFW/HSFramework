project "Core"
	language "C++"
	cppdialect "C++17"
	kind "StaticLib"

	targetdir "%{OutputDir.Binaries}/%{prj.name}"
	objdir "%{OutputDir.Intermediates}/%{prj.name}"

	pchheader "Corepch.h"
	pchsource "Source/Corepch.cpp"

	files
	{
		"Source/**.h",
		"Source/**.cpp"
	}

	includedirs
	{
		"Source",
		
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.spdlog}",
	}

	defines
	{
		"HS_THIS_IS_CORE"
	}
	
	dependson
	{
		"GLFW",
		"Glad"
	}

	filter "system:windows"
		systemversion "latest"
		defines
		{
			"HS_PLATFORM_WINDOWS"
		}

	filter "configurations:Development"
		runtime "Debug"
		symbols "On"
		defines
		{
			"HS_DEVELOPMENT"
		}

	filter "configurations:Preview"
		runtime "Release"
		optimize "Speed"
		defines
		{
			"HS_PREVIEW"
		}

	filter "configurations:Shipping"
		runtime "Release"
		optimize "Speed"
		defines
		{
			"HS_SHIPPING"
		}
