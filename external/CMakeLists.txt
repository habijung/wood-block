set(GLAD_SOURCES glad/src/gl.c)

# Add subdirectories
add_subdirectory(glfw)

# Add libraries
add_library(GLAD STATIC ${GLAD_SOURCES})

# Include
target_include_directories(GLAD PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/glad/include)
