cmake_minimum_required(VERSION 3.21)
project(gear3d_engine)

add_subdirectory(external/SDL)

file(GLOB_RECURSE gear3d_engine_SRC src/*.cpp)
add_library(gear3d_engine STATIC ${gear3d_engine_SRC}
        src/window.cpp)

target_include_directories(gear3d_engine PUBLIC include/)

target_link_libraries(gear3d_engine PRIVATE SDL2::SDL2)