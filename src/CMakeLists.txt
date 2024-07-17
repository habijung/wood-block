cmake_minimum_required(VERSION 3.10)
project(untitled)

add_executable(${PROJECT_NAME}
        main.cpp
        shader.h
        shader.cpp
)

# Find packages
find_package(OpenGL REQUIRED)
find_package(Freetype REQUIRED)

# Target link libraries
target_link_libraries(${PROJECT_NAME} PRIVATE glfw)
target_link_libraries(${PROJECT_NAME} PRIVATE OpenGL::GL)
target_link_libraries(${PROJECT_NAME} PRIVATE GLAD)
target_link_libraries(${PROJECT_NAME} PRIVATE Freetype::Freetype)

# Copy resources
add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/glsl
        $<TARGET_FILE_DIR:${PROJECT_NAME}>/glsl
)
