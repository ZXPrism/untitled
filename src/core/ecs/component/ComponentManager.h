#pragma once

#include "Component.h"
#include "core/Logger.h"
#include "core/ecs/component/ComponentArray.h"
#include "core/ecs/entity/Entity.h"

#include <memory>
#include <unordered_map>

namespace core {

    class ComponentManager
    {
    public:
        template <typename T>
        void RegisterComponent();

        template <typename T>
        ComponentType GetComponentType();

        template <typename T>
        void AddComponent(Entity entity, T component);

        template <typename T>
        void RemoveComponent(Entity entity);

        template <typename T>
        T &GetComponent(Entity entity);

        void EntityDestroyed(Entity entity);

    private:
        // Map from type string pointer to a component type
        std::unordered_map<const char *, ComponentType> _componentTypes;

        // Map from type string pointer to a component
        std::unordered_map<const char *, std::shared_ptr<IComponentArray>> _componentArrays;

        // The component type to be assigned to the next registered component - starting at 0
        ComponentType _nextComponentType = 0;

    private:
        // Convenience function to get the statically cast pointer to the ComponentArray of type T.
        template <typename T>
        std::shared_ptr<ComponentArray<T>> GetComponentArray();
    };

    template <typename T>
    void ComponentManager::RegisterComponent()
    {
        const char *typeName = typeid(T).name();

        LOG_ERROR_COND(_componentTypes.find(typeName) == _componentTypes.end(),
                       "Registering component type <{}> more than once!", typeName);

        LOG_ERROR_COND(_nextComponentType < ECS_MAX_COMPONENTS, "Could not register more components!");

        // Add this component type to the component type map
        _componentTypes.insert({typeName, _nextComponentType});

        // Create a ComponentArray pointer and add it to the component arrays map
        _componentArrays.insert({typeName, std::make_shared<ComponentArray<T>>()});

        // Increase the value so that the next component registered will be different
        ++_nextComponentType;
    }

    template <typename T>
    ComponentType ComponentManager::GetComponentType()
    {
        const char *typeName = typeid(T).name();

        LOG_ERROR_COND(_componentTypes.find(typeName) != _componentTypes.end(),
                       "Component <{}> used before registration!", typeName);

        // Return this component's type - used for creating signatures
        return _componentTypes[typeName];
    }

    template <typename T>
    void ComponentManager::AddComponent(Entity entity, T component)
    {
        // Add a component to the array for an entity
        GetComponentArray<T>()->InsertData(entity, component);
    }

    template <typename T>
    void ComponentManager::RemoveComponent(Entity entity)
    {
        // Remove a component from the array for an entity
        GetComponentArray<T>()->RemoveData(entity);
    }

    template <typename T>
    T &ComponentManager::GetComponent(Entity entity)
    {
        // Get a reference to a component from the array for an entity
        return GetComponentArray<T>()->GetData(entity);
    }

    template <typename T>
    std::shared_ptr<ComponentArray<T>> ComponentManager::GetComponentArray()
    {
        const char *typeName = typeid(T).name();

        LOG_ERROR_COND(_componentTypes.find(typeName) != _componentTypes.end(),
                       "Component <{}> used before registration!", typeName);

        return std::static_pointer_cast<ComponentArray<T>>(_componentArrays[typeName]);
    }

} // namespace core
