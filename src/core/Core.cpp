#include "Core.h"

#include "core/Logger.h"
#include "core/ecs/Coordinator.h"
#include "core/ecs/component/Camera.h"
#include "core/ecs/component/Script.h"
#include "core/ecs/component/Transform.h"
#include "core/ecs/system/CameraSystem.h"
#include "core/ecs/system/RenderSystem.h"
#include "core/ecs/system/ScriptSystem.h"
#include "core/ecs/system/WindowSystem.h"

namespace core {

    void Core::Init()
    {
        gCoordinator.Init();

        // Component Registration
        gCoordinator.RegisterComponent<Transform>();
        gCoordinator.RegisterComponent<Camera>();
        gCoordinator.RegisterComponent<Script>();

        // System Registration
        gCoordinator.RegisterSystem<WindowSystem>()->Init();
        gCoordinator.RegisterSystem<RenderSystem>()->Init();
        gCoordinator.RegisterSystem<ScriptSystem>()->Init();
        gCoordinator.RegisterSystem<CameraSystem>()->Init();

        LOG_STATUS("Core launched.");
    }

    void Core::Run(const std::function<void(float)> &callback)
    {
        auto pWindowSystem = gCoordinator.GetSystem<WindowSystem>();
        auto pRenderSystem = gCoordinator.GetSystem<RenderSystem>();

        while (!pWindowSystem->WindowShouldClose())
        {

            pWindowSystem->BeginFrame();
            pRenderSystem->BeginFrame();

            gCoordinator.UpdateSystems(pWindowSystem->GetDeltaTime());
            callback(pWindowSystem->GetDeltaTime());

            pRenderSystem->EndFrame();
            pWindowSystem->EndFrame();
        }
    }

    void Core::Shutdown()
    {
        gCoordinator.DestorySystem<CameraSystem>();
        gCoordinator.DestorySystem<ScriptSystem>();
        gCoordinator.DestorySystem<RenderSystem>();
        gCoordinator.DestorySystem<WindowSystem>();
    }

} // namespace core
