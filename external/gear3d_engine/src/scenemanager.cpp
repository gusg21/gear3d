//
// Created by angus.goucher on 5/3/2024.
//

#include "g3d/scenemanager.h"

g3d::Scene* g3d::SceneManager::CreateScene() {
    g3d::Scene* newScene = &m_Scenes[m_NextSceneIndex++];
    return newScene;
}

void g3d::SceneManager::SetCurrentScene(g3d::Scene* scene) {
    m_CurrentScene = scene;
}