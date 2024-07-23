#pragma once

#include <functional>

namespace core {

    class Core
    {
    public:
        void Init();
        void Run(const std::function<void(float)> &callback);
        void Shutdown();

    private:
        ;
    };

} // namespace core
