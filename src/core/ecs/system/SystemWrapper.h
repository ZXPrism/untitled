#pragma once

#include "core/ecs/system/System.h"

namespace core {

    class SystemWrapper
    {
    public:
        SystemWrapper() = default;
        explicit SystemWrapper(System *pSystem);

        void Update(float dt);

        bool operator<(SystemWrapper &rhs);

    private:
        System *_pSystem;
        int _priority;
    };

} // namespace core
