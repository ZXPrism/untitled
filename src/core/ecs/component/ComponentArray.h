#pragma once

#include "core/Logger.h"
#include "core/Settings.h"
#include "core/ecs/entity/Entity.h"

#include <array>
#include <unordered_map>

namespace core {

    class IComponentArray
    {
    public:
        virtual ~IComponentArray() = default;
        virtual void EntityDestroyed(Entity entity) = 0;
    };

    template <typename T>
    class ComponentArray : public IComponentArray
    {
    public:
        void InsertData(Entity entity, T component);

        void RemoveData(Entity entity);

        T &GetData(Entity entity);

        virtual void EntityDestroyed(Entity entity) override;

    private:
        // Component array
        std::array<T, ECS_MAX_ENTITIES> _componentArray;

        // Map from an entity ID to an array index
        std::unordered_map<Entity, size_t> _entityToIndexMap;

        // Map from an array index to an entity ID
        std::unordered_map<size_t, Entity> _indexToEntityMap;

        // Total size of valid entries in the array
        size_t _size = 0;
    };

    template <typename T>
    void ComponentArray<T>::InsertData(Entity entity, T component)
    {
        LOG_ERROR_COND(_entityToIndexMap.find(entity) == _entityToIndexMap.end(),
                       "This entity already has a component of type <{}> !", typeid(T).name());

        // Put new entry at end and update the maps
        size_t newIndex = _size;
        _entityToIndexMap[entity] = newIndex;
        _indexToEntityMap[newIndex] = entity;
        _componentArray[newIndex] = component;
        ++_size;
    }

    template <typename T>
    void ComponentArray<T>::RemoveData(Entity entity)
    {
        LOG_ERROR_COND(_entityToIndexMap.find(entity) != _entityToIndexMap.end(),
                       "This entity does not have a component of type <{}> !", typeid(T).name());

        // Copy element at end into deleted element's place to maintain density
        size_t indexOfRemovedEntity = _entityToIndexMap[entity];
        size_t indexOfLastElement = _size - 1;
        _componentArray[indexOfRemovedEntity] = _componentArray[indexOfLastElement];

        // Update map to point to moved spot
        Entity entityOfLastElement = _indexToEntityMap[indexOfLastElement];
        _entityToIndexMap[entityOfLastElement] = indexOfRemovedEntity;
        _indexToEntityMap[indexOfRemovedEntity] = entityOfLastElement;

        _entityToIndexMap.erase(entity);
        _indexToEntityMap.erase(indexOfLastElement);

        --_size;
    }

    template <typename T>
    T &ComponentArray<T>::GetData(Entity entity)
    {
        LOG_ERROR_COND(_entityToIndexMap.find(entity) != _entityToIndexMap.end(),
                       "This entity does not have a component of type <{}> !", typeid(T).name());

        // Return a reference to the entity's component
        return _componentArray[_entityToIndexMap[entity]];
    }

    template <typename T>
    void ComponentArray<T>::EntityDestroyed(Entity entity)
    {
        // Remove the entity's component if it existed
        if (_entityToIndexMap.find(entity) != _entityToIndexMap.end())
        {
            RemoveData(entity);
        }
    }

} // namespace core
