#include "ComponentManager.h"

namespace core {

    void ComponentManager::EntityDestroyed(Entity entity)
    {
        // Notify each component array that an entity has been destroyed
        for (const auto &[name, compArray] : _componentArrays)
        {
            compArray->EntityDestroyed(entity);
        }
    }

} // namespace core
