#include "EntityManager.h"

#include "core/Logger.h"
#include "core/Settings.h"

namespace core {

    EntityManager::EntityManager()
    {
        // Initialize the queue with all possible entity IDs
        for (Entity entity = 0; entity < ECS_MAX_ENTITIES; ++entity)
        {
            _availableEntities.push(entity);
        }
    }

    Entity EntityManager::CreateEntity()
    {
        LOG_ERROR_COND(_livingEntityCount < ECS_MAX_ENTITIES, "Could not create more entities!");

        // Take an ID from the front of the queue
        Entity id = _availableEntities.front();
        _availableEntities.pop();
        ++_livingEntityCount;

        return id;
    }

    void EntityManager::DestroyEntity(Entity entity)
    {
        LOG_ERROR_COND(entity < ECS_MAX_ENTITIES, "Entity ID out of range.");

        // Invalidate the destroyed entity's signature
        _signatures[entity].reset();

        // Put the destroyed ID at the back of the queue
        _availableEntities.push(entity);
        --_livingEntityCount;
    }

    void EntityManager::SetSignature(Entity entity, Signature signature)
    {
        LOG_ERROR_COND(entity < ECS_MAX_ENTITIES, "Entity ID out of range.");

        _signatures[entity] = signature;
    }

    Signature EntityManager::GetSignature(Entity entity)
    {
        LOG_ERROR_COND(entity < ECS_MAX_ENTITIES, "Entity ID out of range.");

        return _signatures[entity];
    }

} // namespace core
