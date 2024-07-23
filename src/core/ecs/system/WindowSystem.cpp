#include "WindowSystem.h"

#include "core/Settings.h"

#include <chrono>

#include <GLFW/glfw3.h>

namespace core {

    void WindowSystem::Init()
    {
        glfwInit();

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, OPENGL_CONTEXT_VER_MAJOR);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, OPENGL_CONTEXT_VER_MINOR);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_SAMPLES, 4);

        _windowHandle = glfwCreateWindow(DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT, DEFAULT_WINDOW_TITLE,
                                         nullptr, nullptr);
        glfwMakeContextCurrent(_windowHandle);
        glfwSwapInterval(0);
    }

    void WindowSystem::Shutdown()
    {
        glfwDestroyWindow(_windowHandle);
        glfwTerminate();
    }

    void WindowSystem::Update(float dt)
    {
    }

    int WindowSystem::GetUpdatePriority() const
    {
        return UPD_PRI_WINDOW_SYSTEM;
    }

    void WindowSystem::BeginFrame()
    {
        _tp1 = std::chrono::steady_clock::now();
    }

    void WindowSystem::EndFrame()
    {
        glfwPollEvents();
        glfwSwapBuffers(_windowHandle);

        _tp2 = std::chrono::steady_clock::now();
        float realDeltaTime =
            std::chrono::duration_cast<std::chrono::microseconds>(_tp2 - _tp1).count() / 1000000.0;
        _deltaTime = DT_FILTER_COFF * _deltaTime + (1 - DT_FILTER_COFF) * realDeltaTime;
    }

    float WindowSystem::GetDeltaTime() const
    {
        return _deltaTime;
    }

    bool WindowSystem::WindowShouldClose() const
    {
        return glfwWindowShouldClose(_windowHandle);
    }

} // namespace core
