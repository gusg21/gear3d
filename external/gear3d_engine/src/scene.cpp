//
// Created by Gus Goucher on 5/2/24.
//

#include "g3d/scene.h"

g3d::Scene::Scene()
    : m_Entities()
    , m_AvailableIds() {
    for (EntityId id = 0; id < ENTITY_MAX_ENTITIES; id++) {
        m_AvailableIds.push(id);
    }
}

g3d::EntityId g3d::Scene::CreateEntity() {
    EntityId newId = m_AvailableIds.front();
    m_AvailableIds.pop();
    m_LivingEntities++;

    return newId;
}

void g3d::Scene::DestroyEntity(g3d::EntityId id) {
    m_Entities[id].reset();
    m_AvailableIds.push(id);
    m_LivingEntities--;
}

void g3d::Scene::SetEntitySignature(g3d::EntityId id, g3d::EntitySignature signature) {
    m_Entities[id] = signature;
}

g3d::EntitySignature g3d::Scene::GetEntitySignature(g3d::EntityId id) {
    return m_Entities[id];
}
