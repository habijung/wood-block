set(GLAD_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/glad/src/gl.c)
set(ASSIMP_CONTRIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/assimp/contrib)

set_property(GLOBAL PROPERTY ASSIMP_CONTRIB ${ASSIMP_CONTRIB_DIR})

# Add subdirectories
add_subdirectory(glfw)
add_subdirectory(glm)
add_subdirectory(assimp)

# Add libraries
add_library(GLAD STATIC ${GLAD_SOURCES})

# Includes
target_include_directories(GLAD PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/glad/include)
