set_project("untitled")

add_rules("mode.debug", "mode.release")
add_requires("glfw", "stb", "glm", "yaml-cpp", "glad", "freetype")
add_requires("imgui", {configs = { glfw = true, opengl3 = true }})

target("untitled")
    set_languages("c99", "cxx17")
    set_kind("binary")
    set_warnings("all")

    add_includedirs("src")
    add_files("src/**.cpp")
    add_packages("glfw", "stb", "glm", "yaml-cpp", "glad", "imgui", "freetype")

    after_build(function (target)
        os.cp(target:targetfile(), "bin/")
        os.cp("assets", "bin/")
    end)
target_end()
