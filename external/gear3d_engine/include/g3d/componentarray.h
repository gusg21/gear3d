//
// Created by Gus Goucher on 5/2/24.
//

#ifndef GEAR3D_COMPONENTARRAY_H
#define GEAR3D_COMPONENTARRAY_H

#include "entity.h"

namespace g3d {
    class IComponentArray {
    public:
        virtual ~IComponentArray() = default;
        virtual void EntityDestroyed(EntityId entity) = 0;
    };

    template<typename T>
    class ComponentArray : public IComponentArray {
    public:
        void InsertData(EntityId id, T component);
        void RemoveData(EntityId id);
        T& GetData(EntityId id);
        void EntityDestroyed(EntityId id) override;

    private:
        std::array<T, ENTITY_MAX_ENTITIES> m_Components;
        std::unordered_map<EntityId, size_t> m_EntityToIndex;
        std::unordered_map<size_t, EntityId> m_IndexToEntity;
        size_t m_Size = 0;

    };

    template<typename T>
    void ComponentArray<T>::InsertData(EntityId id, T component) {
        size_t newIndex = m_Size;
        m_EntityToIndex[id] = newIndex;
        m_IndexToEntity[newIndex] = id;
        m_Components[newIndex] = component;
        m_Size++;
    }

    template<typename T>
    void ComponentArray<T>::RemoveData(EntityId id) {
        size_t removedIndex = m_EntityToIndex[id];
        size_t lastIndex = m_Size - 1;
        m_Components[removedIndex] = m_Components[lastIndex];

        EntityId lastEntity = m_IndexToEntity[lastIndex];
        m_EntityToIndex[lastEntity] = removedIndex;
        m_IndexToEntity[removedIndex] = lastEntity;

        m_EntityToIndex.erase(id);
        m_IndexToEntity.erase(lastIndex);

        m_Size--;
    }

    template<typename T>
    T& ComponentArray<T>::GetData(EntityId entity)
    {
        return m_Components[m_EntityToIndex[entity]];
    }


}

#endif //GEAR3D_COMPONENTARRAY_H
