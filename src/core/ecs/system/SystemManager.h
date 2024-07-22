#pragma once

#include "core/Logger.h"
#include "core/ecs/entity/Entity.h"
#include "core/ecs/system/System.h"
#include "core/ecs/system/SystemWrapper.h"

#include <map>
#include <memory>
#include <unordered_map>

namespace core {

    class SystemManager
    {
    public:
        template <typename T>
        [[nodiscard]] std::shared_ptr<T> RegisterSystem();

        template <typename T>
        void DestorySystem();

        template <typename T>
        std::shared_ptr<T> GetSystem();

        template <typename T>
        void SetSignatureBit(std::uint8_t newSignatureBit);

        template <typename T>
        Signature GetSignature();

        void EntityDestroyed(Entity entity);

        void EntitySignatureChanged(Entity entity, Signature entitySignature);

        void UpdateSystems(float dt);

    private:
        // Map from system type string pointer to a signature
        std::unordered_map<const char *, Signature> _signatures;

        // Map from system type string pointer to a system pointer
        std::unordered_map<const char *, std::shared_ptr<System>> _systems;

        // System map, ordered by priority
        std::map<const char *, SystemWrapper> _updateAuxMap;
    };

    template <typename T>
    std::shared_ptr<T> SystemManager::RegisterSystem()
    {
        const char *typeName = typeid(T).name();

        LOG_ERROR_COND(_systems.find(typeName) == _systems.end(), "Registering system <{}> more than once!",
                       typeName);

        // Create a pointer to the system and return it so it can be used externally
        auto system = std::make_shared<T>();

        _systems.insert({typeName, system});
        _updateAuxMap.insert({typeName, SystemWrapper(system.get())});

        return system;
    }

    template <typename T>
    void SystemManager::DestorySystem()
    {
        const char *typeName = typeid(T).name();

        LOG_ERROR_COND(_systems.find(typeName) != _systems.end(),
                       "Could not destory system <{}> since it hasn't been created yet!", typeName);

        _systems[typeName]->Shutdown();
        _systems[typeName].reset();

        // TODO: remove the destoryed system from each data structure
    }

    template <typename T>
    std::shared_ptr<T> SystemManager::GetSystem()
    {
        const char *typeName = typeid(T).name();

        LOG_ERROR_COND(_systems.find(typeName) != _systems.end(),
                       "Could not get system <{}> since it hasn't been created yet!", typeName);

        return std::static_pointer_cast<T>(_systems[typeName]);
    }

    template <typename T>
    void SystemManager::SetSignatureBit(std::uint8_t newSignatureBit)
    {
        const char *typeName = typeid(T).name();

        LOG_ERROR_COND(_systems.find(typeName) != _systems.end(),
                       "Could not add new signatures to system <{}> since it hasn't been created yet!",
                       typeName);

        _signatures[typeName].set(newSignatureBit);
    }

    template <typename T>
    Signature SystemManager::GetSignature()
    {
        const char *typeName = typeid(T).name();

        LOG_ERROR_COND(_systems.find(typeName) != _systems.end(),
                       "Could not get the signature of system <{}> since it hasn't been created yet!",
                       typeName);

        return _signatures[typeName];
    }

} // namespace core
