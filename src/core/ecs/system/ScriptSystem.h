#pragma once

#include "System.h"

namespace core {

    class ScriptSystem : public System
    {
    public:
        virtual void Init() override;
        virtual void InitSignatures() override;
        virtual void Shutdown() override;

        virtual void Update(float dt) override;
        virtual int GetUpdatePriority() const override;
    };

} // namespace core
