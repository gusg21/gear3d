//
// Created by angus.goucher on 5/2/2024.
//

#ifndef GEAR3D_ENGINE_GAME_H
#define GEAR3D_ENGINE_GAME_H

#include "window.h"

namespace g3d
{
	class Game
	{
	 public:
		explicit Game(const WindowSettings& windowSettings);
		Game(const Game&) = delete;
		Game& operator=(const Game&) = delete;

	 private:
		g3d::Window m_Window;
	};
}

#endif //GEAR3D_ENGINE_GAME_H
