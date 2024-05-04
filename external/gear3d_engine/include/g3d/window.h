//
// Created by angus.goucher on 5/2/2024.
//

#ifndef GEAR3D_EXAMPLE_WINDOW_H
#define GEAR3D_EXAMPLE_WINDOW_H

#include <string>

#include <SDL.h>

namespace g3d {
    struct WindowSettings {
        uint32_t Width = 1600, Height = 900;
        std::string Title = "Gear3D Window";
    };

    class Window {
    public:
        explicit Window(const WindowSettings& windowSettings);
        Window(const Window&) = delete;
        Window& operator=(const Window&) = delete;

        [[nodiscard]] void* GetInternalHandle() const;

    private:
        SDL_Window* m_Window;
    };
}

#endif //GEAR3D_EXAMPLE_WINDOW_H
