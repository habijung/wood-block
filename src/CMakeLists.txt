add_executable(${PROJECT_NAME}
        main.cpp
        shader.h
        shader.cpp
)

# Find packages
find_package(OpenGL REQUIRED)

# Target link libraries
target_link_libraries(${PROJECT_NAME} glfw)
target_link_libraries(${PROJECT_NAME} OpenGL::GL)
target_link_libraries(${PROJECT_NAME} GLAD)

# Copy resources
add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/glsl
        $<TARGET_FILE_DIR:${PROJECT_NAME}>/glsl
)
