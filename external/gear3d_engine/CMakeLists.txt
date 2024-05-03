cmake_minimum_required(VERSION 3.21)
project(gear3d_engine)

set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

add_subdirectory(external/SDL)

file(GLOB_RECURSE gear3d_engine_SRC src/*.cpp)
add_library(gear3d_engine STATIC ${gear3d_engine_SRC}
        src/window.cpp include/g3d/scene.h include/g3d/entity.h src/scene.cpp include/g3d/component.h include/g3d/componentarray.h src/componentarray.cpp
        include/g3d/componentmanager.h
        src/componentmanager.cpp
        include/g3d/system.h
        include/g3d/systemmanager.h
        include/g3d/entitymanager.h
        src/entitymanager.cpp
        src/systemmanager.cpp
        include/g3d/scenemanager.h
        src/scenemanager.cpp)

target_include_directories(gear3d_engine PUBLIC include/)

target_link_libraries(gear3d_engine PUBLIC SDL2::SDL2)
target_link_libraries(gear3d_engine PUBLIC SDL2::SDL2main)

