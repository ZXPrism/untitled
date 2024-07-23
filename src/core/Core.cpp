#include "Core.h"

#include "core/ecs/Coordinator.h"
#include "core/ecs/system/WindowSystem.h"

namespace core {

    void Core::Init()
    {
        gCoordinator.Init();

        // Component Registration

        // System Registration
        gCoordinator.RegisterSystem<WindowSystem>()->Init();
    }

    void Core::Run(const std::function<void(float)> &callback)
    {
        auto pWindowSystem = gCoordinator.GetSystem<WindowSystem>();

        while (!pWindowSystem->WindowShouldClose())
        {
            pWindowSystem->BeginFrame();
            pWindowSystem->EndFrame();
        }
    }

    void Core::Shutdown()
    {
        gCoordinator.DestorySystem<WindowSystem>();
    }

} // namespace core
