#pragma once

#include "core/ecs/entity/Entity.h"

#include <set>

namespace core {

    class System
    {
        friend class SystemManager;

    public:
        virtual ~System() = default;

        virtual void Init() = 0;
        virtual void InitSignatures() = 0;
        virtual void Shutdown() = 0;

        virtual void Update(float dt) = 0;
        virtual int GetUpdatePriority() const = 0;

    protected:
        std::set<Entity> _entities;
    };

} // namespace core
