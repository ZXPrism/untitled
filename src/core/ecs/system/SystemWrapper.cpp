#include "SystemWrapper.h"

namespace core {

    SystemWrapper::SystemWrapper(System *pSystem) : _pSystem(pSystem)
    {
        _priority = pSystem->GetUpdatePriority();
    }

    void SystemWrapper::Update(float dt)
    {
        _pSystem->Update(dt);
    }

    bool SystemWrapper::operator<(SystemWrapper &rhs)
    {
        return _priority < rhs._priority;
    }

} // namespace core
