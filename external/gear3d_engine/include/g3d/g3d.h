//
// Created by angus.goucher on 5/2/2024.
//

#ifndef GEAR3D_ENGINE_G3D_H
#define GEAR3D_ENGINE_G3D_H

#include <cstdio>

#include "game.h"

#include "systems/renderer/renderer.h"

#define GEAR3D_VERSION_MAJOR 0
#define GEAR3D_VERSION_MINOR 1
#define GEAR3D_BUILD_DATE __DATE__
#define GEAR3D_BUILD_TIME __TIME__

namespace g3d
{
	static void PrintVersionInfo()
	{
		printf("Gear3d v%d.%d built at %s on %s\n", GEAR3D_VERSION_MAJOR, GEAR3D_VERSION_MINOR, GEAR3D_BUILD_TIME,
			GEAR3D_BUILD_DATE);
	}
}

#endif //GEAR3D_ENGINE_G3D_H
