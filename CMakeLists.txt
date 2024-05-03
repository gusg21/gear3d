cmake_minimum_required(VERSION 3.21)
project(gear3d_example)
set(CMAKE_CXX_STANDARD 11)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

add_subdirectory(external/gear3d_engine)

file(GLOB_RECURSE gear3d_example_SRC src/*.cpp)
add_executable(gear3d_example_EXE ${gear3d_example_SRC})

target_link_libraries(gear3d_example_EXE PUBLIC gear3d_engine)
