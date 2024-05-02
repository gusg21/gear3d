cmake_minimum_required(VERSION 3.21)
project(gear3d_example)

add_subdirectory(external/gear3d_engine)

file(GLOB_RECURSE gear3d_example_SRC src/*.cpp)
add_executable(gear3d_example_EXE ${gear3d_example_SRC})

target_link_libraries(gear3d_example_EXE PUBLIC gear3d_engine)