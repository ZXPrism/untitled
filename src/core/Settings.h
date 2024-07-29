#pragma once

namespace core {

    // Logger
    constexpr const char *LOG_FILE_PATH = "untitled.log";

    // ECS
    constexpr int ECS_MAX_ENTITIES = 100000;
    constexpr int ECS_MAX_COMPONENTS = 32;

    // System Update Priority
    // Basic Rule: Logic always comes first
    constexpr int UPD_PRI_WINDOW_SYSTEM = 2;
    constexpr int UPD_PRI_RENDER_SYSTEM = 2;
    constexpr int UPD_PRI_SCRIPT_SYSTEM = 0;
    constexpr int UPD_PRI_CAMERA_SYSTEM = 1;

    // OpenGL
    constexpr int OPENGL_CONTEXT_VER_MAJOR = 4;
    constexpr int OPENGL_CONTEXT_VER_MINOR = 5;

    // Window
    constexpr int DEFAULT_WINDOW_WIDTH = 1920;
    constexpr int DEFAULT_WINDOW_HEIGHT = 1080;
    constexpr const char *DEFAULT_WINDOW_TITLE = "untitled b2407a";
    constexpr float DT_FILTER_COFF = 0.9f;

    // Shader
    constexpr const char *SHADER_VERT_COLORPASS_PATH = "assets/shaders/color.vs";
    constexpr const char *SHADER_FRAG_COLORPASS_PATH = "assets/shaders/color.fs";

} // namespace core
