include "Globals.lua"

workspace "HSFramework"
	architecture "x64"
	configurations
	{
		"Development",
		"Preview",
		"Shipping"
	}
	startproject "Runtime" -- Change to Editor later when we actually have an editor :-)

group "Vendor"
	include "Vendor/GLFW"
	include "Vendor/Glad"
group ""

include "Core"
include "Editor"
include "Runtime"
