//
// Created by Gus Goucher on 5/2/24.
//

#ifndef GEAR3D_ENTITY_H
#define GEAR3D_ENTITY_H

#include <bitset>
#include "component.h"

#define ENTITY_MAX_ENTITIES 1024

namespace g3d {
	using EntityId = uint32_t; // Bwahahaha
	using EntitySignature = std::bitset<COMPONENT_MAX_COMPONENTS>;
}

#endif //GEAR3D_ENTITY_H
