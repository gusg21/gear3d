//
// Created by angus.goucher on 5/2/2024.
//

#ifndef GEAR3D_COMPONENTMANAGER_H
#define GEAR3D_COMPONENTMANAGER_H

#include <typeinfo>

#include "component.h"
#include "componentarray.h"

namespace g3d {
    class ComponentManager {
    public:
        ComponentManager() = default;
        ComponentManager(const ComponentManager&) = delete;
        ComponentManager& operator=(const ComponentManager&) = delete;

        template<typename T>
        void RegisterComponent();

        template<typename T>
        ComponentType GetComponentType();

        template<typename T>
        void AddComponent(EntityId entity, T component);

        template<typename T>
        void RemoveComponent(EntityId entity);

        template<typename T>
        T& GetComponent(EntityId entity);

        void EntityDestroyed(EntityId entity);

    private:
        std::unordered_map<const char*, ComponentType> m_ComponentTypes { };
        std::unordered_map<const char*, IComponentArray*> m_ComponentArrays { };
        ComponentType mNextComponentType { };

        template<typename T>
        ComponentArray<T>* GetComponentArray() {
            const char* typeName = typeid(T).name();

            return m_ComponentArrays[typeName];
        }
    };

    template<typename T>
    void ComponentManager::RegisterComponent() {
        const char* typeName = typeid(T).name();

        m_ComponentTypes.insert(
            { typeName, mNextComponentType }
        );

        m_ComponentArrays.insert(
            { typeName, new ComponentArray<T>() }
        );

        mNextComponentType++;
    }

    template<typename T>
    ComponentType ComponentManager::GetComponentType() {
        const char* typeName = typeid(T).name();

        return m_ComponentTypes[typeName];
    }

    template<typename T>
    void ComponentManager::AddComponent(EntityId entity, T component) {
        GetComponentArray<T>()->InsertData(entity, component);
    }

    template<typename T>
    void ComponentManager::RemoveComponent(EntityId entity) {
        GetComponentArray<T>()->RemoveData(entity);
    }

    template<typename T>
    T& ComponentManager::GetComponent(EntityId entity) {
        return GetComponentArray<T>()->GetData(entity);
    }
}

#endif // GEAR3D_COMPONENTMANAGER_H
