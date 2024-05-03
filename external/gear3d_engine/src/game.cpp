//
// Created by angus.goucher on 5/2/2024.
//

#include "g3d/game.h"

#include "g3d/systemmanager.h"
#include "g3d/componentmanager.h"

namespace g3d {
    Game::Game(const WindowSettings& windowSettings, const RendererSettings& rendererSettings)
        : m_Window(windowSettings)
        , m_Renderer(rendererSettings)
        , m_Systems()
        , m_Scenes() { }

    void Game::Run(g3d::Scene* initialScene) {
    }

    template<typename T>
    T* Game::RegisterSystem() {
        return m_Systems.RegisterSystem<T>();
    }

    template<typename T>
    void Game::SetSystemSignature(g3d::EntitySignature signature) {
        m_Systems.SetSignature<T>(signature);
    }
}
