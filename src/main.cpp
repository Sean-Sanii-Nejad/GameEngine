#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "graphics/Renderer2D.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>


void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

int main() {
    // Initialize GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW\n";
        return -1;
    }

    // Setup OpenGL context version and profile
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create window
    GLFWwindow* window = glfwCreateWindow(800, 600, "2D Renderer", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window\n";
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Load OpenGL function pointers via GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD\n";
        return -1;
    }

    // Set viewport
    glViewport(0, 0, 800, 600);

    // Create Renderer2D instance and initialize
    Renderer2D renderer;
    renderer.Init();

    // Setup orthographic projection: left=0, right=800, bottom=0, top=600
    glm::mat4 projection = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f);
    glm::mat4 view = glm::mat4(1.0f);  // Identity view matrix for no camera movement
    glm::mat4 viewProjection = projection * view;

    // Main loop
    while (!glfwWindowShouldClose(window)) {
        // Input: close on ESC
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);

        // Clear screen with dark blue-ish color
        glClearColor(0.1f, 0.1f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Begin scene with view-projection matrix
        renderer.BeginScene(viewProjection);

        // Draw a magenta quad at (100, 100), size (200x150)
        renderer.DrawQuad({ 100.0f, 100.0f }, { 200.0f, 150.0f }, { 1.0f, 0.0f, 1.0f, 1.0f });

        // End scene (optional)
        renderer.EndScene();

        // Swap buffers and poll events
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Cleanup
    renderer.Shutdown();
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}

