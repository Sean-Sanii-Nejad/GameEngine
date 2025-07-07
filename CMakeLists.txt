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

    # Source files
    src/graphics/Shader.cpp
    src/graphics/Renderer2D.cpp
    src/graphics/Texture2D.cpp
    src/graphics/SubTexture2D.cpp

    # Header files
    include/graphics/Shader.h
    include/graphics/Renderer2D.h
    include/graphics/Texture2D.h
    include/graphics/SubTexture2D.h
    include/stb/stb_image.h
)

# Include directories
target_include_directories(GameEngine
    PUBLIC
    include               # Your engine headers
    include/stb          # For stb_image.h
    libs/glad/include    # GLAD headers
    libs/glfw/include    # GLFW headers
    libs/glm             # GLM math library
)

# Link libraries
target_link_libraries(GameEngine
    glad
    glfw
)

# Copy shaders to build output
file(GLOB SHADERS "shaders/*.vert" "shaders/*.frag")
foreach(SHADER ${SHADERS})
    configure_file(${SHADER} ${CMAKE_CURRENT_BINARY_DIR}/shaders/ COPYONLY)
endforeach()
