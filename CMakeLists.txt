cmake_minimum_required(VERSION 3.10)
project(GameEngine)

set(CMAKE_CXX_STANDARD 17)

# Source files
set(SOURCES
    src/App/main.cpp
    src/App/AppWindow.cpp
    src/App/Game.cpp
    src/Engine/GraphicsEngine.cpp
    src/Engine/Window.cpp
    src/Engine/SwapChain.cpp
    src/Engine/DeviceContext.cpp
)

# Header search paths
include_directories(
    include           # Engine headers
    include/App       # Application-specific headers
    include/Engine    # Engine-specific headers
    include/stb       # For stb_image.h or other single-header libs
    libs/glm          # If using GLM
)

# Create executable
add_executable(GameEngine ${SOURCES})

# Link DirectX 11 libraries
target_link_libraries(GameEngine
    d3d11
    dxgi
    d3dcompiler
)


