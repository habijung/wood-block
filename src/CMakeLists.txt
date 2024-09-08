cmake_minimum_required(VERSION 3.10)
project(untitled)

set(CMAKE_CXX_STANDARD 17)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set(SOURCES
        camera/Camera.cpp
        camera/Camera.h
        mesh/Mesh.cpp
        mesh/Mesh.h
        mesh/Model.cpp
        mesh/Model.h
        render/RenderText.cpp
        render/RenderText.h
        shader/Shader.h
        shader/Shader.cpp
)

add_executable(${PROJECT_NAME}
        main.cpp
        ${SOURCES}
)

set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Get global properties
get_property(ASSIMP_CONTRIB GLOBAL PROPERTY ASSIMP_CONTRIB)

# Find packages
find_package(OpenGL REQUIRED)
find_package(Freetype REQUIRED)

# Includes
target_include_directories(${PROJECT_NAME} PRIVATE ${ASSIMP_CONTRIB}/stb)

# Link libraries
target_link_libraries(${PROJECT_NAME} PRIVATE glfw)
target_link_libraries(${PROJECT_NAME} PRIVATE OpenGL::GL)
target_link_libraries(${PROJECT_NAME} PRIVATE GLAD)
target_link_libraries(${PROJECT_NAME} PRIVATE Freetype::Freetype)
target_link_libraries(${PROJECT_NAME} PRIVATE glm::glm)
target_link_libraries(${PROJECT_NAME} PRIVATE assimp::assimp)

# Copy resources
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/data
        $<TARGET_FILE_DIR:${PROJECT_NAME}>/data)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/glsl
        $<TARGET_FILE_DIR:${PROJECT_NAME}>/glsl)

# Copy shared libraries
if (WIN32)
    file(GLOB SHARED_LIBS
            ${CMAKE_BINARY_DIR}/external/assimp/bin/*.dll
            ${CMAKE_BINARY_DIR}/external/glfw/src/*.dll
            ${CMAKE_BINARY_DIR}/external/glm/glm/*.dll
    )

    foreach (SHARED_LIB ${SHARED_LIBS})
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy_if_different
                ${SHARED_LIB}
                $<TARGET_FILE_DIR:${PROJECT_NAME}>)
    endforeach ()
endif ()
