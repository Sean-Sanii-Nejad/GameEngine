cmake_minimum_required(VERSION 3.10)
project(GameEngine)

set(CMAKE_CXX_STANDARD 17)

# GLFW
add_subdirectory(libs/glfw)

# GLAD
add_library(glad STATIC libs/glad/src/glad.c)
target_include_directories(glad PUBLIC libs/glad/include)

# Your executable
add_executable(GameEngine src/main.cpp)

target_include_directories(GameEngine
    PUBLIC
    libs/glad/include
    libs/glfw/include
)

target_link_libraries(GameEngine
    glad
    glfw
)
