//
// Created by angus.goucher on 5/2/2024.
//
#include "g3d/componentmanager.h"

void g3d::ComponentManager::EntityDestroyed(EntityId entity) {
    for (auto const& pair : m_ComponentArrays)
    {
        auto const& component = pair.second;

        component->EntityDestroyed(entity);
    }
}

