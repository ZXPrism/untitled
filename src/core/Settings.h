#pragma once

namespace core {

    // Logger
    constexpr const char *LOG_FILE_PATH = "untitled.log";

    // ECS
    constexpr int ECS_MAX_ENTITIES = 100000;
    constexpr int ECS_MAX_COMPONENTS = 32;

    // System Update Priority
    constexpr int UPD_PRI_WINDOW_SYSTEM = 0;

    // OpenGL
    constexpr int OPENGL_CONTEXT_VER_MAJOR = 4;
    constexpr int OPENGL_CONTEXT_VER_MINOR = 5;

    // Window
    constexpr int DEFAULT_WINDOW_WIDTH = 1280;
    constexpr int DEFAULT_WINDOW_HEIGHT = 960;
    constexpr const char *DEFAULT_WINDOW_TITLE = "untitled b2407a";
    constexpr float DT_FILTER_COFF = 0.9f;

} // namespace core
