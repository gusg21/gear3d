//
// Created by angus.goucher on 5/2/2024.
//

#include "g3d/entitymanager.h"

g3d::EntityManager::EntityManager()
    : m_Entities()
    , m_AvailableIds() {
    for (EntityId id = 0; id < ENTITY_MAX_ENTITIES; id++) {
        m_AvailableIds.push(id);
    }
}

g3d::EntityId g3d::EntityManager::CreateEntity() {
    EntityId newId = m_AvailableIds.front();
    m_AvailableIds.pop();
    m_LivingEntities++;

    return newId;
}

void g3d::EntityManager::DestroyEntity(g3d::EntityId id) {
    m_Entities[id].reset();
    m_AvailableIds.push(id);
    m_LivingEntities--;
}

void g3d::EntityManager::SetEntitySignature(g3d::EntityId id, g3d::EntitySignature signature) {
    m_Entities[id] = signature;
}

g3d::EntitySignature g3d::EntityManager::GetEntitySignature(g3d::EntityId id) {
    return m_Entities[id];
}
