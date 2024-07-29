#include "core/Core.h"
#include "core/ecs/Coordinator.h"
#include "core/ecs/component/Camera.h"
#include "core/ecs/component/Script.h"
#include "core/ecs/component/Transform.h"

int main(int argc, char *argv[])
{
    using namespace core;

    Core core;

    core.Init();

    // test codes BEGIN

    // borders
    auto AddBorder = [&](float x, float y) {
        auto ent = gCoordinator.CreateEntity();
        Transform comTransform;
        comTransform._pos = {x, y, 0.0f};
        comTransform._scale = {10.0f, 10.0f, 1.0f};
        gCoordinator.AddComponent(ent, comTransform);
    };

    AddBorder(0, 10);
    AddBorder(0, -10);
    AddBorder(-10, 0);
    AddBorder(10, 0);

    // player
    auto entPlayer = gCoordinator.CreateEntity();
    Transform comTransform;
    comTransform._pos.x = 1.0f;
    gCoordinator.AddComponent(entPlayer, comTransform);

    Script comScriptPlayer;
    comScriptPlayer._callback = [&](Entity entity, float dt) {
        static float t = 0.0f;
        t += dt;
        auto &comTransform = gCoordinator.GetComponent<Transform>(entity);
        comTransform._rotation.z = 50 * t;

        static int dx = 10, dy = 8;
        comTransform._pos.x += dt * dx;
        comTransform._pos.y += dt * dy;

        if (comTransform._pos.x <= -5 || comTransform._pos.x > 5)
        {
            dx = -dx;
        }

        if (comTransform._pos.y <= -5 || comTransform._pos.y > 5)
        {
            dy = -dy;
        }
    };
    gCoordinator.AddComponent(entPlayer, comScriptPlayer);

    // camera
    auto entCamera = gCoordinator.CreateEntity();
    Camera comCamera;
    comCamera.Perspective(90.0 / 180.0 * 3.141592653, 1.0 * DEFAULT_WINDOW_WIDTH / DEFAULT_WINDOW_HEIGHT,
                          0.1f, 100.0f);
    gCoordinator.AddComponent(entCamera, comCamera);

    Script comScript;
    comScript._callback = [&](Entity entity, float dt) {
        constexpr glm::vec3 off = {0.0f, 0.0f, 7.0f};

        auto &comCamera = gCoordinator.GetComponent<Camera>(entity);
        auto &comTransform = gCoordinator.GetComponent<Transform>(entPlayer);

        comCamera._pos = comTransform._pos + off;
    };
    gCoordinator.AddComponent(entCamera, comScript);

    // test codes END

    core.Run([&](float dt) {});
    core.Shutdown();

    return 0;
}
