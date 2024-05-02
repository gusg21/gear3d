//
// Created by angus.goucher on 5/2/2024.
//

#include "g3d/window.h"

#include <SDL.h>

namespace g3d {

    Window::Window(const WindowSettings &windowSettings) {
        m_Window = SDL_CreateWindow(windowSettings.Title.c_str(),
                                              SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                              (int) windowSettings.Width, (int) windowSettings.Height,
                                              SDL_VIDEO_VULKAN);

    }
}