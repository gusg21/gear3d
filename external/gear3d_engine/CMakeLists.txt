cmake_minimum_required(VERSION 3.21)
project(gear3d_engine)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

# Vendored SDKs
add_subdirectory(external/SDL)
set(BUILD_SHARED_LIBS OFF)
add_subdirectory(external/glm)

# System-wide SDKs (developer must install!)
message("Vulkan SDK: " $ENV{VULKAN_SDK})
message("void* size: " ${CMAKE_SIZEOF_VOID_P})
find_package(Vulkan REQUIRED)

# Library definition
file(GLOB_RECURSE gear3d_engine_SRC src/*.cpp)
add_library(gear3d_engine STATIC ${gear3d_engine_SRC} include/g3d/builddefs.h)

# Library defines
if (APPLE)
    target_compile_definitions(gear3d_engine PUBLIC APPLE)
endif ()
if (WIN32)
    target_compile_definitions(gear3d_engine PUBLIC WIN32)
endif ()

# Library includes
target_include_directories(gear3d_engine PUBLIC include/)

# SDK linking
target_link_libraries(gear3d_engine PUBLIC SDL2::SDL2)
if (WIN32)
    target_link_libraries(gear3d_engine PUBLIC SDL2::SDL2main)
endif ()

target_link_libraries(gear3d_engine PUBLIC glm::glm)

target_link_libraries(gear3d_engine PUBLIC Vulkan::Vulkan)

