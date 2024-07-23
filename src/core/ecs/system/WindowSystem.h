#pragma once

#include "System.h"

#include <chrono>

struct GLFWwindow;

namespace core {

    class WindowSystem : public System
    {
    public:
        virtual void Init() override;
        virtual void Shutdown() override;

        virtual void Update(float dt) override;
        virtual int GetUpdatePriority() const override;

        void BeginFrame();
        void EndFrame();

        float GetDeltaTime() const;
        bool WindowShouldClose() const;

    private:
        GLFWwindow *_windowHandle;

        std::chrono::steady_clock::time_point _tp1, _tp2;
        float _deltaTime;
    };

} // namespace core
