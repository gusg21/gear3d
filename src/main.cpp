//
// Created by angus.goucher on 5/2/2024.
//

#include "g3d/g3d.h"

// Windows entry point
int SDL_main(int argc, char** argv) {
    // A little info
    g3d::PrintVersionInfo();

    // Initialize a new game with the given settings
    g3d::Game game {
        g3d::WindowSettings {},
        g3d::RendererSettings {}
    };

    // Run the game!
    // game.Run(/* initial scene pointer */);

    return 0;
}

// macOS (only?) entry point, wraps Windows entry point
int main(int argc, char** argv) {
    return SDL_main(argc, argv); // TODO: is there a better option? this is only needed on macOS (afaik) - gus
}