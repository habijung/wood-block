add_executable(${PROJECT_NAME} main.cpp)

# Find packages
find_package(OpenGL REQUIRED)

# Target link libraries
target_link_libraries(${PROJECT_NAME} glfw)
target_link_libraries(${PROJECT_NAME} OpenGL::GL)
target_link_libraries(${PROJECT_NAME} GLAD)
