#include "core/Core.h"

int main(int argc, char *argv[])
{
    core::Core core;

    core.Init();
    core.Run([&](float dt) {});
    core.Shutdown();

    return 0;
}
