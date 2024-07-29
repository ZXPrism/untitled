#include "RenderSystem.h"

#include "core/Logger.h"
#include "core/Settings.h"
#include "core/ecs/Coordinator.h"
#include "core/ecs/component/Camera.h"
#include "core/ecs/component/Transform.h"
#include "core/ecs/system/CameraSystem.h"

#include <glad/glad.h>

namespace core {

    void RenderSystem::Init()
    {
        InitSignatures();

        gladLoadGL();
        glViewport(0, 0, DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT);
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_MULTISAMPLE);

        // ONLY FOR TEST
        ShaderInfo shaderInfo;
        shaderInfo._vertexShaderPath = SHADER_VERT_COLORPASS_PATH;
        shaderInfo._fragmentShaderPath = SHADER_FRAG_COLORPASS_PATH;
        _colorPassShader.Init(shaderInfo);

        InitModels();

        LOG_STATUS("RenderSystem inited.");
    }

    void RenderSystem::InitSignatures()
    {
        gCoordinator.AddSystemSignature<RenderSystem, Transform>();
    }

    void RenderSystem::Shutdown()
    {
        LOG_STATUS("RenderSystem shutdown.");
    }

    void RenderSystem::Update(float dt)
    {
        auto &sceneCamera = gCoordinator.GetSystem<CameraSystem>()->GetSceneCamera();
        auto viewMatrix = sceneCamera._viewMatrix;
        auto projMatrix = sceneCamera._projectionMatrix;

        _colorPassShader.Activate();
        _colorPassShader.SetUniform("view", viewMatrix);
        _colorPassShader.SetUniform("proj", projMatrix);

        for (auto entity : _entities)
        {
            auto &comTransform = gCoordinator.GetComponent<Transform>(entity);
            comTransform.UpdateModelMatrix(); // lazy strategy -  update only when needed

            _colorPassShader.SetUniform("model", comTransform._modelMatrix);

            _ModelQuad.DrawTriangles(0, 6);
        }
    }

    int RenderSystem::GetUpdatePriority() const
    {
        return UPD_PRI_RENDER_SYSTEM;
    }

    void RenderSystem::BeginFrame()
    {
        glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    }

    void RenderSystem::EndFrame()
    {
    }

    void RenderSystem::InitModels()
    {
        float quadVertices[] = {-0.5f, 0.5f, 0.0f, 1.0f, 0.5f, -0.5f, 1.0f, 0.0f, -0.5f, -0.5f, 0.0f, 0.0f,
                                -0.5f, 0.5f, 0.0f, 1.0f, 0.5f, 0.5f,  1.0f, 1.0f, 0.5f,  -0.5f, 1.0f, 0.0f};

        _ModelQuad.SetData(&quadVertices[0], sizeof(quadVertices) / sizeof(float))
            .SetUsage(0, 2)
            .SetUsage(1, 2)
            .EndSetUsage();
    }

} // namespace core
