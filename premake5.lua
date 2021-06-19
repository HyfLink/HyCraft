inc = {}
inc["glm"] = "vendor/glm/include"
inc["glad"] = "vendor/glad/include"
inc["glfw"] = "vendor/glfw/include"
inc["spdlog"] = "vendor/spdlog/include"
inc["HyJson"] = "project/HyJson/include"
inc["HyEngine"] = "project/HyEngine/include"

workspace "HyWorkspace"
    language "C++"
    cppdialect "C++17"
    location "build"
    architecture "x64"
    configurations { "debug", "release" }

    objdir ("build/%{cfg.longname}/%{prj.name}")
    libdirs { "build/lib" }

project "glad"
    kind "StaticLib"
    optimize "Full"
    targetdir ("build/lib")
    includedirs { inc["glad"] }
    files { "vendor/glad/include/**", "vendor/glad/src/**" }

project "glfw"
    kind "StaticLib"
    optimize "Full"
    targetdir ("build/lib")
    includedirs { inc["glfw"], inc["glad"] }
    files { "vendor/glfw/include/**", "vendor/glad/src/**" }
    links { "glad" }

project "spdlog"
    kind "StaticLib"
    optimize "Full"
    targetdir ("build/lib")
    defines { "SPDLOG_COMPILED_LIB" }

    includedirs { inc["spdlog"] }
    files { "vendor/spdlog/include/**", "vendor/spdlog/src/**" }

project "HyJson"
    kind "StaticLib"
    targetdir ("build/lib")

    includedirs { inc["HyJson"] }
    files { "project/HyJson/include/**", "project/HyJson/src/**" }

    filter { "configurations:debug" }
        defines { "DEBUG" }
        symbols "On"

    filter { "configurations:release" }
        defines { "NDEBUG" }
        optimize "Full"

project "Sandbox"
    kind "ConsoleApp"
    targetdir ("build/bin")
    targetname "main"
    includedirs { "project/Sandbox/include", inc["HyJson"] }
    files { "project/Sandbox/**" }
    links { "HyJson" }
    
    defines { "DEBUG" }
    symbols "On"
