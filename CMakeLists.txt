cmake_minimum_required(VERSION 3.10)
project(GameEngine)

set(CMAKE_CXX_STANDARD 17)

# GLFW
add_subdirectory(libs/glfw)

# GLAD
add_library(glad STATIC libs/glad/src/glad.c)
target_include_directories(glad PUBLIC libs/glad/include)

# Your executable (GameEngine)
add_executable(GameEngine
    src/main.cpp
    src/graphics/Shader.cpp
    src/graphics/Renderer2D.cpp
    include/graphics/Renderer2D.h
    include/graphics/Shader.h
)

# Include directories for the main project
target_include_directories(GameEngine
    PUBLIC
    include
    libs/glad/include
    libs/glfw/include
    libs/glm  # ✅ this is the correct level
)

# Link libraries
target_link_libraries(GameEngine
    glad
    glfw
)

# Copy shaders to output directory
file(GLOB SHADERS "shaders/*.vert" "shaders/*.frag")
foreach(SHADER ${SHADERS})
    configure_file(${SHADER} ${CMAKE_CURRENT_BINARY_DIR}/shaders/ COPYONLY)
endforeach()
