//
// Created by angus.goucher on 5/3/2024.
//

#ifndef GEAR3D_RENDERER_H
#define GEAR3D_RENDERER_H

#include <SDL.h>
#include <vulkan/vulkan.h>

#include "g3d/system.h"
#include "g3d/window.h"

#define RENDERER_ENGINE_NAME "Gear3d Engine v" GEAR3D_VERSION_MAJOR "." #GEAR3D_VERSION_MINOR

namespace g3d {
    struct RendererSettings {
        std::string AppName = "Gear3d App";
    };

    class Renderer : public System {
    public:
        explicit Renderer(const RendererSettings& settings);
        Renderer(const Renderer&) = delete;
        Renderer& operator=(const Renderer&) = delete;
        ~Renderer();

        void InitializeFromWindow(g3d::Window* window);
        void Render();

        // Is the renderer good to use?
        [[nodiscard]] bool IsOk() const { return m_Ok; }

    private:
        bool m_Ok = false;

        g3d::RendererSettings m_Settings;
        VkInstance m_Instance;
    };
}

#endif //GEAR3D_RENDERER_H
