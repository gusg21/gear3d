cmake_minimum_required(VERSION 3.21)
project(gear3d_engine)

set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

# Vendored SDKs
add_subdirectory(external/SDL)
set(BUILD_SHARED_LIBS OFF)
add_subdirectory(external/glm)

# System-wide SDKs (developer must install!)
find_package(Vulkan REQUIRED)

# Library def
file(GLOB_RECURSE gear3d_engine_SRC src/*.cpp)
add_library(gear3d_engine STATIC ${gear3d_engine_SRC})

# Library includes
target_include_directories(gear3d_engine PUBLIC include/)

# SDK linking
target_link_libraries(gear3d_engine PUBLIC SDL2::SDL2)
target_link_libraries(gear3d_engine PUBLIC SDL2::SDL2main)

target_link_libraries(gear3d_engine PUBLIC glm::glm)

target_link_libraries(gear3d_engine PUBLIC Vulkan::Vulkan)

