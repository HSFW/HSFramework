project "Runtime"
	language "C++"
	cppdialect "C++17"
	
	targetdir "%{OutputDir.Binaries}/%{prj.name}"
	objdir "%{OutputDir.Intermediates}/%{prj.name}"

	files
	{
		"Source/**.h",
		"Source/**.cpp"
	}

	includedirs
	{
		"%{IncludeDir.Core}",
		"Source",

		"%{IncludeDir.glm}",
		"%{IncludeDir.spdlog}"
	}

	defines
	{
		"HS_THIS_IS_RUNTIME"
	}

	links
	{
		-- Prerequisites of the project "Core"
		"GLFW",
		"Glad",

		"Core"
	}

	filter "system:windows"
		systemversion "latest"
		defines
		{
			"HS_PLATFORM_WINDOWS"
		}

	filter "configurations:Development"
		kind "ConsoleApp"
		runtime "Debug"
		symbols "On"
		defines
		{
			"HS_DEVELOPMENT"
		}

	filter "configurations:Preview"
		kind "ConsoleApp"
		runtime "Release"
		optimize "Speed"
		defines
		{
			"HS_PREVIEW"
		}

	filter "configurations:Shipping"
		kind "WindowedApp"
		runtime "Release"
		optimize "Speed"
		defines
		{
			"HS_SHIPPING"
		}
