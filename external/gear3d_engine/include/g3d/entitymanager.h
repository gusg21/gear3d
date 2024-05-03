//
// Created by angus.goucher on 5/2/2024.
//

#ifndef GEAR3D_ENTITYMANAGER_H
#define GEAR3D_ENTITYMANAGER_H

#include <queue>
#include <array>

#include "entity.h"

#define ENTITYMANAGER_MAX_NUM_ENTITIES 1024

namespace g3d {
    class EntityManager {
    public:
        EntityManager();
        EntityManager(const EntityManager&) = delete;
        EntityManager& operator=(const EntityManager&) = delete;

        [[nodiscard]] EntityId CreateEntity();
        void DestroyEntity(EntityId id);
        void SetEntitySignature(EntityId id, EntitySignature signature);
        [[nodiscard]] EntitySignature GetEntitySignature(EntityId id);

    private:
        std::queue<EntityId> m_AvailableIds;
        std::array<EntitySignature, ENTITYMANAGER_MAX_NUM_ENTITIES> m_Entities;
        uint32_t m_LivingEntities = 0;
    };
}

#endif //GEAR3D_ENTITYMANAGER_H
