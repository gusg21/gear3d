//
// Created by angus.goucher on 5/3/2024.
//

#ifndef GEAR3D_SCENEMANAGER_H
#define GEAR3D_SCENEMANAGER_H

#include "scene.h"

#define SCENE_MANAGER_MAX_NUM_SCENES 32

namespace g3d {
    class SceneManager {
    public:
        SceneManager() = default;
        SceneManager(const SceneManager&) = delete;
        SceneManager& operator=(const SceneManager&) = delete;

        void SetCurrentScene(g3d::Scene* scene);
        g3d::Scene* CreateScene();

    private:
        std::array<g3d::Scene, SCENE_MANAGER_MAX_NUM_SCENES> m_Scenes;
        g3d::Scene* m_CurrentScene = nullptr;
        uint32_t m_NextSceneIndex = 0;
    };
}

#endif //GEAR3D_SCENEMANAGER_H
