#include "CameraSystem.h"

#include "core/Logger.h"
#include "core/Settings.h"
#include "core/ecs/Coordinator.h"
#include "core/ecs/component/Camera.h"

namespace core {

    void CameraSystem::Init()
    {
        InitSignatures();

        LOG_STATUS("CameraSystem inited.");
    }

    void CameraSystem::InitSignatures()
    {
        gCoordinator.AddSystemSignature<CameraSystem, Camera>();
    }

    void CameraSystem::Shutdown()
    {
        LOG_STATUS("CameraSystem shutdown.");
    }

    void CameraSystem::Update(float dt)
    {
        for (auto entity : _entities)
        {
            auto &comCamera = gCoordinator.GetComponent<Camera>(entity);
            comCamera.UpdateMatrices();
        }
    }

    int CameraSystem::GetUpdatePriority() const
    {
        return UPD_PRI_CAMERA_SYSTEM;
    }

    const Camera &CameraSystem::GetSceneCamera()
    {
        return gCoordinator.GetComponent<Camera>(*_entities.begin());
    }

} // namespace core
