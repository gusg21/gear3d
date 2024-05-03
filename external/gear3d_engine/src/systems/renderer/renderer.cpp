//
// Created by angus.goucher on 5/3/2024.
//

#include "g3d/systems/renderer/renderer.h"

g3d::Renderer::Renderer(const RendererSettings& settings) {
    printf("Renderer initializing...\n");

    uint32_t extensionCount = 0;
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);

    printf("%d extensions supported.\n", extensionCount);

    // Create instance
    VkApplicationInfo appInfo {};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = settings.AppName.c_str();
    appInfo.pEngineName = "Gear3d Renderer";

    printf("Renderer initialized!\n");
}

void g3d::Renderer::Render() {
}
