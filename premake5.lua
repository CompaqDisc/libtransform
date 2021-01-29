workspace "libtransform"
	architecture "x86_64"
	configurations { "debug", "release" }

project "transform"
	language "C++"
	cppdialect "C++17"
	kind "StaticLib"

	targetdir "bin/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}/%{prj.name}"
	objdir  "build/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}/%{prj.name}"

	files {
		"src/%{prj.name}/**.hh"
	}

	includedirs {
		"src/"
	}

	filter "configurations:debug*"
		defines { "DEBUG" }
		symbols "On"

	filter "configurations:release*"
		defines { "NDEBUG" }
		optimize "On"

project "test"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"

	targetdir "bin/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}/%{prj.name}"
	objdir  "build/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}/%{prj.name}"

	files {
		"src/%{prj.name}/**.cc"
	}

	includedirs {
		"src/"
	}

	filter "configurations:debug*"
		defines { "DEBUG" }
		symbols "On"

	filter "configurations:release*"
		defines { "NDEBUG" }
		optimize "On"
