//
// Created by angus.goucher on 5/2/2024.
//

#ifndef GEAR3D_ENGINE_GAME_H
#define GEAR3D_ENGINE_GAME_H

#include <array>
#include "window.h"
#include "scene.h"
#include "scenemanager.h"

#define GAME_MAX_NUM_SCENES 32

namespace g3d
{
	class Game
	{
	 public:
		explicit Game(const WindowSettings& windowSettings);
		Game(const Game&) = delete;
		Game& operator=(const Game&) = delete;

        // Running
        void Run(g3d::Scene* initialScene);

        // Systems
        template<typename T>
        T* RegisterSystem();
        template<typename T>
        void SetSystemSignature(EntitySignature signature);

	 private:
		g3d::Window m_Window;
        g3d::SystemManager m_Systems;
        g3d::SceneManager m_Scenes;
	};
}

#endif //GEAR3D_ENGINE_GAME_H
