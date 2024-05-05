//
// Created by angus.goucher on 5/3/2024.
//

#ifndef GEAR3D_RENDERER_H
#define GEAR3D_RENDERER_H

#include <vector>

#include <SDL.h>
#include <vulkan/vulkan.h>

#include "g3d/system.h"
#include "g3d/window.h"

#define RENDERER_ENGINE_NAME "Gear3d Engine v" GEAR3D_VERSION_MAJOR "." #GEAR3D_VERSION_MINOR

namespace g3d {
    struct RendererSettings {
        std::string AppName = "Gear3d App";
    };

    struct QueueFamilyIndices {
        bool IsGraphicsFamilyValid = false;
        uint32_t GraphicsFamily = 0;
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
        static std::vector<const char*> GetRequiredExtensions(
            g3d::Window* window, bool requiresPortability,
            bool requiresDebugUtils
        );
        static VKAPI_ATTR VkBool32 VKAPI_CALL DebugCallback(
            VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
            VkDebugUtilsMessageTypeFlagsEXT messageType,
            const VkDebugUtilsMessengerCallbackDataEXT* callbackData,
            void* userData
        );
        static VkResult CreateDebugUtilsMessengerEXT(
            VkInstance instance,
            const VkDebugUtilsMessengerCreateInfoEXT* createInfo,
            const VkAllocationCallbacks* allocator,
            VkDebugUtilsMessengerEXT* debugMessenger
        );
        static VkResult DestroyDebugUtilsMessengerEXT(
            VkInstance instance,
            VkDebugUtilsMessengerEXT debugMessenger,
            const VkAllocationCallbacks* allocator
        );
        static bool IsDeviceSuitable(VkPhysicalDevice device);
        static QueueFamilyIndices FindQueueFamilies(VkPhysicalDevice device);

        bool m_Ok = false;
        bool m_UsingValidationLayers = false;
        bool m_UsingPortabilityExtension = false;

        g3d::RendererSettings m_Settings;

        VkInstance m_Instance = VK_NULL_HANDLE;
        VkDebugUtilsMessengerEXT m_DebugMessenger = VK_NULL_HANDLE;
        VkPhysicalDevice m_PhysicalDevice = VK_NULL_HANDLE;
        VkDevice m_Device = VK_NULL_HANDLE;
        VkQueue m_GraphicsQueue = VK_NULL_HANDLE;
    };
}

#endif //GEAR3D_RENDERER_H
