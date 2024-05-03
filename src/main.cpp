//
// Created by angus.goucher on 5/2/2024.
//

#include "g3d/g3d.h"

int SDL_main(int argc, char** argv) {
    g3d::PrintVersionInfo();

    g3d::Game game {
        g3d::WindowSettings {}
    };

    return 0;
}