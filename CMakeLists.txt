cmake_minimum_required(VERSION 3.28)
project(untitled)

# Add subdirectories
add_subdirectory(external)

set(CMAKE_CXX_STANDARD 17)

add_executable(untitled main.cpp)

# Find packages
find_package(OpenGL REQUIRED)

# Target link libraries
target_link_libraries(untitled glfw)
target_link_libraries(untitled OpenGL::GL)
