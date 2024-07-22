#include "SystemManager.h"

namespace core {

    void SystemManager::EntityDestroyed(Entity entity)
    {
        // Erase a destroyed entity from all system lists
        // _entities is a set so no check needed
        for (const auto &[name, system] : _systems)
        {
            system->_entities.erase(entity);
        }
    }

    void SystemManager::EntitySignatureChanged(Entity entity, Signature entitySignature)
    {
        // Notify each system that an entity's signature changed
        for (const auto &[name, system] : _systems)
        {
            const auto &systemSignature = _signatures[name];

            // Entity signature matches system signature - insert into set
            if ((entitySignature & systemSignature) == systemSignature)
            {
                system->_entities.insert(entity);
            }
            // Entity signature does not match system signature - erase from set
            else
            {
                system->_entities.erase(entity);
            }
        }
    }

    void SystemManager::UpdateSystems(float dt)
    {
        for (auto &[name, system] : _updateAuxMap)
        {
            system.Update(dt);
        }
    }

} // namespace core
