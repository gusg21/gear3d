//
// Created by angus.goucher on 5/3/2024.
//

#include "g3d/systems/renderer/renderer.h"

#include <SDL_vulkan.h>

#include "g3d/builddefs.h"
#include "g3d/window.h"

g3d::Renderer::Renderer(const RendererSettings& settings)
    : m_Settings(settings) { }

g3d::Renderer::~Renderer() {
    if (m_Ok) { // TODO: Clumsy!
        vkDestroyInstance(m_Instance, nullptr);
    }
}

/**
 *     TODO: With SDL2, the existence of a Renderer requires the existence of a Window.
 *      Therefore, we should probably make a Renderer be owned by the window instead of doing this weird
 *      function tango?
 */
void g3d::Renderer::InitializeFromWindow(g3d::Window* window) {
    /*
     * WARNING! If you're not Gus or maybe someone else with Vulkan knowledge, get outta here!
     * Light reading: https://vulkan-tutorial.com/resources/vulkan_tutorial_en.pdf
     *
     * Abandon all hope, ye who enter...
     */

    printf("INFO: RENDERER: Renderer initializing...\n");

    // Determine number of extensions system provides
//    uint32_t extensionCount = 0;
//    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
//    printf("INFO: RENDERER: %d extensions supported.\n", extensionCount);

    // Create app info
    VkApplicationInfo appInfo { };
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = m_Settings.AppName.c_str();
    appInfo.applicationVersion = VK_MAKE_API_VERSION(0, 1, 2, 3);
    appInfo.pEngineName = "Gear3d Renderer";
    appInfo.engineVersion = VK_MAKE_API_VERSION(0, GEAR3D_VERSION_MAJOR, GEAR3D_VERSION_MINOR, 0);
    appInfo.apiVersion = VK_API_VERSION_1_0; // TODO: keep up-to-date

    // Get SDL's required extensions
    uint32_t sdlExtensionCount = 0;
    const char** sdlExtensions = nullptr;
    SDL_Vulkan_GetInstanceExtensions((SDL_Window*)window->GetInternalHandle(), &sdlExtensionCount, sdlExtensions);

    printf("INFO: RENDERER: SDL requires %d extensions.\n", sdlExtensionCount);

    // Create creation info (I hate you Vulkan API)
    VkInstanceCreateInfo createInfo { };
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo;
    createInfo.enabledLayerCount = 0;

#ifdef WIN32
    // Windows gets to use the extensions as-is because it plays nice with Vulkan
    createInfo.enabledExtensionCount = sdlExtensionCount;
    createInfo.ppEnabledExtensionNames = sdlExtensions;
#endif
#ifdef APPLE
    // Apple needs a freaking compatibility extension because Steve Jobs has a personal vendetta against me only
    std::vector<const char*> sdlExtensionsVec { };

    // Copy all the base extensions to a vector
    for (uint32_t i = 0; i < sdlExtensionCount; i++) {
        sdlExtensionsVec.emplace_back(sdlExtensions[i]);
    }

    // Set the portability flag + add it to the extensions
    sdlExtensionsVec.emplace_back(VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME);
    createInfo.flags |= VK_INSTANCE_CREATE_ENUMERATE_PORTABILITY_BIT_KHR;

    // Apply to createInfo
    createInfo.enabledExtensionCount = (uint32_t)sdlExtensionsVec.size();
    createInfo.ppEnabledExtensionNames = sdlExtensionsVec.data();
#endif

    // Create the Vulkan instance itself
    VkResult result = vkCreateInstance(&createInfo, nullptr, &m_Instance);
    if (result != VK_SUCCESS) {
        printf("ERROR: RENDERER: Failed to create Vulkan instance! Error code %d", result);
        return;
    }

    // TODO: Validation layers up next! @gusg21

    // Everything went smoothly, mark the renderer as a-ok.
    printf("INFO: RENDERER: Renderer initialized successfully\n");
    m_Ok = true;
}

void g3d::Renderer::Render() {
}

