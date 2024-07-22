#pragma once

#include "core/Settings.h"
#include "core/ecs/entity/Entity.h"

#include <array>
#include <queue>

namespace core {

    class EntityManager
    {
    public:
        EntityManager();

        [[nodiscard]] Entity CreateEntity();
        void DestroyEntity(Entity entity);

        void SetSignature(Entity entity, Signature signature);
        Signature GetSignature(Entity entity);

    private:
        std::queue<Entity> _availableEntities;
        std::array<Signature, ECS_MAX_ENTITIES> _signatures;
        uint32_t _livingEntityCount = 0;
    };

} // namespace core
