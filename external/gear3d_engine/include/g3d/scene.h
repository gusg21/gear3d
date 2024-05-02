//
// Created by Gus Goucher on 5/2/24.
//

#ifndef GEAR3D_ENGINE_SCENE_H
#define GEAR3D_ENGINE_SCENE_H

#include <array>
#include <queue>

#include "entity.h"

#define SCENE_MAX_NUM_ENTITIES 1024

namespace g3d {
	class Scene {
	public:
		Scene();
		Scene(const Scene&) = delete;
		Scene& operator=(const Scene&) = delete;

        [[nodiscard]] EntityId CreateEntity();
        void DestroyEntity(EntityId id);
        void SetEntitySignature(EntityId id, EntitySignature signature);
        [[nodiscard]] EntitySignature GetEntitySignature(EntityId id);

        template<typename T>
        void RegisterComponent();
        

    private:
		std::queue<EntityId> m_AvailableIds;
		std::array<EntitySignature, SCENE_MAX_NUM_ENTITIES> m_Entities;
		uint32_t m_LivingEntities = 0;
	};
}

#endif //GEAR3D_ENGINE_SCENE_H
