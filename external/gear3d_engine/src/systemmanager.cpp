//
// Created by angus.goucher on 5/2/2024.
//

#include "g3d/systemmanager.h"

void g3d::SystemManager::EntityDestroyed(g3d::EntityId entity) {
    for (auto const& pair : m_Systems) {
        auto const& system = pair.second;

        system->m_Entities.erase(entity);
    }
}

void g3d::SystemManager::EntitySignatureChanged(g3d::EntityId entity, g3d::EntitySignature entitySignature) {
    for (auto const& pair : m_Systems)
    {
        auto const& type = pair.first;
        auto const& system = pair.second;
        auto const& systemSignature = m_Signatures[type];

        if ((entitySignature & systemSignature) == systemSignature)
        {
            system->m_Entities.insert(entity);
        }
        else
        {
            system->m_Entities.erase(entity);
        }
    }

}
