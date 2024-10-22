OutputDir = { }
OutputDir["__Completer__"] = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
OutputDir["Binaries"] = "%{wks.location}/Binaries/%{OutputDir.__Completer__}"
OutputDir["Intermediates"] = "%{wks.location}/Binaries-Int/%{OutputDir.__Completer__}"

ProjectDir = { }
ProjectDir["Core"] = "%{wks.location}/Core"
ProjectDir["Editor"] = "%{wks.location}/Editor"
ProjectDir["Runtime"] = "%{wks.location}/Runtime"
ProjectDir["GLFW"] = "%{wks.location}/Vendor/GLFW"
ProjectDir["Glad"] = "%{wks.location}/Vendor/Glad"

IncludeDir = { }
IncludeDir["Core"] = "%{ProjectDir.Core}/Source"
IncludeDir["Editor"] = "%{ProjectDir.Editor}/Source"
IncludeDir["Runtime"] = "%{ProjectDir.Runtime}/Source"
IncludeDir["GLFW"] = "%{ProjectDir.GLFW}/include"
IncludeDir["Glad"] = "%{ProjectDir.Glad}/include"
IncludeDir["glm"] = "%{wks.location}/Vendor/glm"
IncludeDir["spdlog"] = "%{wks.location}/Vendor/spdlog/include"

SourceDir = { }
SourceDir["Core"] = "%{IncludeDir.Core}"
SourceDir["Editor"] = "%{IncludeDir.Editor}"
SourceDir["Runtime"] = "%{IncludeDir.Runtime}"
SourceDir["GLFW"] = "%{ProjectDir.GLFW}/src"
SourceDir["Glad"] = "%{ProjectDir.Glad}/src"
