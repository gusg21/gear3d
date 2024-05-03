//
// Created by angus.goucher on 5/3/2024.
//

#ifndef GEAR3D_RENDERER_H
#define GEAR3D_RENDERER_H

#include "g3d/system.h"

#include <SDL.h>
#include <vulkan/vulkan.h>

#define RENDERER_ENGINE_NAME "Gear3d Engine v" GEAR3D_VERSION_MAJOR "." #GEAR3D_VERSION_MINOR

namespace g3d {
    struct RendererSettings {
        std::string AppName = "Gear3d App";
    };

    class Renderer : public System {
    public:
        Renderer(const RendererSettings& settings);

        void Render();

    private:
        VkInstance m_Instance;
    };
}

#endif //GEAR3D_RENDERER_H
