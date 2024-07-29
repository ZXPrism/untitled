#pragma once

#include "System.h"

#include "core/resource/Shader.h"
#include "core/resource/VertexBuffer.h"

namespace core {

    class RenderSystem : public System
    {
    public:
        virtual void Init() override;
        virtual void InitSignatures() override;
        virtual void Shutdown() override;

        virtual void Update(float dt) override;
        virtual int GetUpdatePriority() const override;

        void BeginFrame();
        void EndFrame();

    private:
        void InitModels();

    private:
        Shader _colorPassShader; // ONLY FOR TEST, it should be loaded through ResourceSystem
        VertexBuffer _ModelQuad;
    };

} // namespace core
