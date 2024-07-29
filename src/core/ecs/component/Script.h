#pragma once

#include "core/ecs/entity/Entity.h"

#include <functional>

namespace core {

    class Script
    {
    public:
        // parameters: <entity> <delta_time>
        std::function<void(Entity, float)> _callback;
    };

} // namespace core
