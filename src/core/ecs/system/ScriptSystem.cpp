#include "ScriptSystem.h"

#include "core/Logger.h"
#include "core/Settings.h"
#include "core/ecs/Coordinator.h"
#include "core/ecs/component/Script.h"

namespace core {

    void ScriptSystem::Init()
    {
        InitSignatures();

        LOG_STATUS("ScriptSystem inited.");
    }

    void ScriptSystem::InitSignatures()
    {
        gCoordinator.AddSystemSignature<ScriptSystem, Script>();
    }

    void ScriptSystem::Shutdown()
    {
        LOG_STATUS("ScriptSystem shutdown.");
    }

    void ScriptSystem::Update(float dt)
    {
        for (auto entity : _entities)
        {
            auto &comScript = gCoordinator.GetComponent<Script>(entity);
            comScript._callback(entity, dt);
        }
    }

    int ScriptSystem::GetUpdatePriority() const
    {
        return UPD_PRI_SCRIPT_SYSTEM;
    }

} // namespace core
