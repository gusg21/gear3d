//
// Created by Gus Goucher on 5/2/24.
//

#ifndef GEAR3D_ENGINE_SCENE_H
#define GEAR3D_ENGINE_SCENE_H

#include <array>
#include <queue>

#include "entity.h"
#include "entitymanager.h"
#include "componentmanager.h"
#include "systemmanager.h"

namespace g3d {
	class Scene {
	public:
		Scene();
		Scene(const Scene&) = delete;
		Scene& operator=(const Scene&) = delete;

        EntityId CreateEntity();
        void DestroyEntity(EntityId id);

        template<typename T>
        void RegisterComponent();
        template<typename T>
        void AddComponent(EntityId id, T component);
        template<typename T>
        void RemoveComponent(EntityId id);
        template<typename T>
        T& GetComponent(EntityId id);
        template<typename T>
        ComponentType GetComponentType();

    private:
        g3d::EntityManager m_Entities;
        g3d::ComponentManager m_Components;
	};
}

#endif //GEAR3D_ENGINE_SCENE_H
