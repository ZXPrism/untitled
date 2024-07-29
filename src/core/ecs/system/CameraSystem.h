#pragma once

#include "System.h"
#include "core/ecs/component/Camera.h"

namespace core {

    class CameraSystem : public System
    {
    public:
        virtual void Init() override;
        virtual void InitSignatures() override;
        virtual void Shutdown() override;

        virtual void Update(float dt) override;
        virtual int GetUpdatePriority() const override;

        const Camera &GetSceneCamera(); // ONLY for test since we haven't had a "Scene" concept for now
    };

} // namespace core
