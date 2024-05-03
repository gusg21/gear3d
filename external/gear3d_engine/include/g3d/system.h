//
// Created by angus.goucher on 5/2/2024.
//

#ifndef GEAR3D_SYSTEM_H
#define GEAR3D_SYSTEM_H

#include <set>
#include "entity.h"

namespace g3d {
    class System {
    public:
        System() = default;
        System(const System&) = delete;
        System& operator=(const System&) = delete;

        std::set<EntityId> m_Entities;
    };
}

#endif //GEAR3D_SYSTEM_H
