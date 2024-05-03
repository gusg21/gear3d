//
// Created by Gus Goucher on 5/2/24.
//

#include "g3d/scene.h"

#include "g3d/entitymanager.h"

g3d::Scene::Scene()
    : m_Entities()
    , m_Components() { }

g3d::EntityId g3d::Scene::CreateEntity() {
    return m_Entities.CreateEntity();
}

void g3d::Scene::DestroyEntity(g3d::EntityId id) {
    m_Entities.DestroyEntity(id);
}

template<typename T>
void g3d::Scene::RemoveComponent(g3d::EntityId id) {
    m_Components.RemoveComponent<T>(id);
}

template<typename T>
void g3d::Scene::AddComponent(g3d::EntityId id, T component) {
    m_Components.AddComponent<T>(id, component);
}

template<typename T>
void g3d::Scene::RegisterComponent() {
    m_Components.RegisterComponent<T>();
}

template<typename T>
T& g3d::Scene::GetComponent(g3d::EntityId id) {
    return m_Components.GetComponent<T>(id);
}

template<typename T>
g3d::ComponentType g3d::Scene::GetComponentType() {
    return m_Components.GetComponentType<T>();
}
