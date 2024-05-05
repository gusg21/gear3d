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
        if (m_UsingValidationLayers) {
            DestroyDebugUtilsMessengerEXT(m_Instance, m_DebugMessenger, nullptr);
        }

        vkDestroyDevice(m_Device, nullptr);
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

    // Create creation info (I hate you Vulkan API)
    VkInstanceCreateInfo createInfo { };
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo;

#ifdef APPLE // Thanks Steve Jobs
    m_UsingPortabilityExtension = true;
    createInfo.flags |= VK_INSTANCE_CREATE_ENUMERATE_PORTABILITY_BIT_KHR;
#endif

#ifdef GEAR3D_USE_VALIDATION_LAYERS
    m_UsingValidationLayers = true;
#endif

    std::vector<const char*>
        requiredExtensions = GetRequiredExtensions(window, m_UsingPortabilityExtension, m_UsingValidationLayers);
    createInfo.ppEnabledExtensionNames = requiredExtensions.data();
    createInfo.enabledExtensionCount = requiredExtensions.size();

    printf("INFO: RENDERER: %lu required extensions found\n", requiredExtensions.size());

    // Validation layers
#ifdef GEAR3D_USE_VALIDATION_LAYERS
    std::vector<const char*> validationLayers = {
        "VK_LAYER_KHRONOS_validation"
    };

    createInfo.ppEnabledLayerNames = validationLayers.data();
    createInfo.enabledLayerCount = validationLayers.size();
#else
    createInfo.ppEnabledLayerNames = nullptr;
    createInfo.enabledLayerCount = 0;
#endif

    // Create the Vulkan instance itself
    VkResult createResult = vkCreateInstance(&createInfo, nullptr, &m_Instance);
    if (createResult != VK_SUCCESS) {
        printf("ERROR: RENDERER: Failed to create Vulkan instance! Error code %d\n", createResult);
        switch (createResult) {
            case VK_ERROR_LAYER_NOT_PRESENT:
                printf(
                    "ERROR: RENDERER: Missing validation layers required for Debug builds, do you have the SDK "
                    "installed?\n"
                );
                break;
            case VK_ERROR_INCOMPATIBLE_DRIVER:
                printf(
                    "ERROR: RENDERER: Drivers do not support Vulkan; is the compatibility extension required and "
                    "not enabled?\n"
                );
                break;
            default:
                break;

                // TODO: other relevant cases
        }
        return;
    }

    // Debug Messenger
    VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo { };
    debugCreateInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
    debugCreateInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT |
        VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT |
        VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
        VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
    debugCreateInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT
        | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
        VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
    debugCreateInfo.pfnUserCallback = DebugCallback;

    VkResult debugCreateResult = CreateDebugUtilsMessengerEXT(m_Instance, &debugCreateInfo, nullptr, &m_DebugMessenger);
    if (debugCreateResult != VK_SUCCESS) {
        printf("ERROR: RENDERER: Unable to set up debug messenger! Error code: %d\n", debugCreateResult);
        return;
    }

    // Pick physical device
    uint32_t deviceCount = 0;
    vkEnumeratePhysicalDevices(m_Instance, &deviceCount, nullptr);
    std::vector<VkPhysicalDevice> devices(deviceCount);
    vkEnumeratePhysicalDevices(m_Instance, &deviceCount, devices.data());

    if (deviceCount < 1) {
        printf("ERROR: RENDERER: No GPUs support Vulkan!\n");
        return;
    }

    printf("INFO: RENDERER: %d physical devices available\n", deviceCount);

    for (const auto& device : devices) {
        if (IsDeviceSuitable(device)) {
            m_PhysicalDevice = device;
            break;
        }
    }

    if (m_PhysicalDevice == VK_NULL_HANDLE) {
        printf("ERROR: RENDERER: No GPUs are suitable!\n");
        return;
    }

    // Logical Device
    QueueFamilyIndices indices = FindQueueFamilies(m_PhysicalDevice);

    VkDeviceQueueCreateInfo queueCreateInfo { };
    queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    queueCreateInfo.queueFamilyIndex = indices.GraphicsFamily;
    queueCreateInfo.queueCount = 1;
    float queuePriority = 1.0f;
    queueCreateInfo.pQueuePriorities = &queuePriority;

    VkPhysicalDeviceFeatures physicalDeviceFeatures { };

    VkDeviceCreateInfo logicalDeviceCreateInfo { };
    logicalDeviceCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    logicalDeviceCreateInfo.pQueueCreateInfos = &queueCreateInfo;
    logicalDeviceCreateInfo.queueCreateInfoCount = 1;
    logicalDeviceCreateInfo.pEnabledFeatures = &physicalDeviceFeatures;

#ifdef GEAR3D_USE_VALIDATION_LAYERS
    // Use the same layers for compatibility's sake; these should be ignored by all reasonably recent
    //  Vulkan implementations.
    logicalDeviceCreateInfo.ppEnabledLayerNames = validationLayers.data();
    logicalDeviceCreateInfo.enabledLayerCount = validationLayers.size();
#else
    // Or don't.
    logicalDeviceCreateInfo.ppEnabledLayerNames = nullptr;
    logicalDeviceCreateInfo.enabledLayerCount = 0;
#endif

    VkResult logicalDeviceCreateResult = vkCreateDevice(
        m_PhysicalDevice,
        &logicalDeviceCreateInfo,
        nullptr,
        &m_Device
    );
    if (logicalDeviceCreateResult != VK_SUCCESS) {
        printf("ERROR: RENDERER: Unable to create logical device! Error code: %d\n", logicalDeviceCreateResult);
        return;
    }

    // Grab the queue created by the logical device
    vkGetDeviceQueue(m_Device, indices.GraphicsFamily, 0, &m_GraphicsQueue);

    // Everything went smoothly, mark the renderer as a-ok.
    printf("INFO: RENDERER: Renderer initialized successfully\n");
    m_Ok = true;
}

void g3d::Renderer::Render() {
}

std::vector<const char*> g3d::Renderer::GetRequiredExtensions(
    g3d::Window* window, bool requiresPortability,
    bool requiresDebugUtils
) {
    std::vector<const char*> extensionsVec { };

    // Get SDL's required extensions
    uint32_t sdlExtensionCount = 0;
    const char** sdlExtensions = nullptr;
    SDL_Vulkan_GetInstanceExtensions((SDL_Window*)window->GetInternalHandle(), &sdlExtensionCount, sdlExtensions);

    for (uint32_t i = 0; i < sdlExtensionCount; i++) {
        extensionsVec.push_back(sdlExtensions[i]);
    }

    if (requiresPortability) {
        extensionsVec.push_back(VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME);
    }

    if (requiresDebugUtils) {
        extensionsVec.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
    }

    return extensionsVec;
}

VkBool32 g3d::Renderer::DebugCallback(
    VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType,
    const VkDebugUtilsMessengerCallbackDataEXT* callbackData, void* userData
) {
    switch (messageSeverity) {
        case VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT:
//            printf("DEBUG: RENDERER: ");
            return VK_FALSE;
            break;
        case VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT:
            printf("INFO: RENDERER: ");
            break;
        case VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT:
            printf("WARNING: RENDERER: ");
            break;
        case VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT:
            printf("ERROR: RENDERER: ");
            break;
        default:
            break;
    }

    printf("%s\n", callbackData->pMessage);

    return VK_FALSE;
}

VkResult g3d::Renderer::CreateDebugUtilsMessengerEXT(
    VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* createInfo, const VkAllocationCallbacks* allocator,
    VkDebugUtilsMessengerEXT* debugMessenger
) {
    auto func = (PFN_vkCreateDebugUtilsMessengerEXT)
        vkGetInstanceProcAddr(
            instance,
            "vkCreateDebugUtilsMessengerEXT"
        );
    if (func != nullptr) {
        return func(instance, createInfo, allocator, debugMessenger);
    } else {
        return VK_ERROR_EXTENSION_NOT_PRESENT;
    }
}

VkResult g3d::Renderer::DestroyDebugUtilsMessengerEXT(
    VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* allocator
) {
    auto func = (PFN_vkDestroyDebugUtilsMessengerEXT)
        vkGetInstanceProcAddr(
            instance,
            "vkDestroyDebugUtilsMessengerEXT"
        );
    if (func != nullptr) {
        func(instance, debugMessenger, allocator);
    }

    return VK_SUCCESS;
}

bool g3d::Renderer::IsDeviceSuitable(VkPhysicalDevice device) {
//    VkPhysicalDeviceProperties deviceProps { };
//    vkGetPhysicalDeviceProperties(device, &deviceProps);
//
//    VkPhysicalDeviceFeatures deviceFeatures { };
//    vkGetPhysicalDeviceFeatures(device, &deviceFeatures);

    g3d::QueueFamilyIndices indices = FindQueueFamilies(device);

    return indices.IsGraphicsFamilyValid;
}

g3d::QueueFamilyIndices g3d::Renderer::FindQueueFamilies(VkPhysicalDevice device) {
    g3d::QueueFamilyIndices indices { };

    uint32_t queueFamilyCount = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

    std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

    uint32_t i = 0;
    for (const auto& queueFamily : queueFamilies) {
        if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
            indices.GraphicsFamily = i;
            indices.IsGraphicsFamilyValid = true;
            break;
        }

        i++;
    }

    return indices;
}

