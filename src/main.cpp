#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

float vertices[] = {
    // Positions        // Colors (R, G, B)
     0.0f,  0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  // Top — Red
    -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  // Bottom left — Green
     0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f   // Bottom right — Blue
};


/*
 * Takes in aPos and aColor
 * Outputs a screen-space position and forwards the color to the fragment shader.
 */

const char* vertexShaderSource = R"(
#version 460 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec3 ourColor;

void main() {
    gl_Position = vec4(aPos, 1.0);
    ourColor = aColor;
}
)";

/*
 * Takes the interpolated color from the vertex shader and paints each pixel.
 */
const char* fragmentShaderSource = R"(
#version 460 core
in vec3 ourColor;
out vec4 FragColor;

void main() {
    FragColor = vec4(ourColor, 1.0);
}
)";

/*
 * Initialises VAO and VBO for a triangle with position and colour attributes.
 * Vertex format: [x, y, z, r, g, b]. Returns the VAO ID.
 */

unsigned int createTriangleVAO(float* vertices, size_t dataSize)
{
	unsigned int VAO, VBO; // Generate Unique IDs for Vertex Array Object (VAO) and Vertex Buffer Object (VBO) 
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    // bind VAO
	glBindVertexArray(VAO); // bind VAO (how to interpret the data)
	glBindBuffer(GL_ARRAY_BUFFER, VBO); // bind VBO (where the data is stored)
	glBufferData(GL_ARRAY_BUFFER, dataSize, vertices, GL_STATIC_DRAW); // Upload vertex data to the GPU

    // Position attribute (location = 0)
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0); // 3 floats per vertex (x, y, z)
    glEnableVertexAttribArray(0);

    // Color attribute (location = 1)
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float))); // 3 floats per color (r, g, b)
    glEnableVertexAttribArray(1);

	// unbind VAO and VBO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    return VAO;
}

/*
 * Complies and links a vertex and fragment shader into a shader program.
 * Returns the shader program ID.
 */

unsigned int createShaderProgram(const char* vertexSrc, const char* fragmentSrc) {
    // Vertex Shader
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexSrc, nullptr);
    glCompileShader(vertexShader);

    // Fragment Shader
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentSrc, nullptr);
    glCompileShader(fragmentShader);

    // Shader Program
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // Cleanup
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;
}


int main() {

	if (!glfwInit()) { // Check if GLFW is initialized successfully
        std::cerr << "Failed to initialize GLFW\n";
        return -1;
    }

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); // Set OpenGL version to 4.6, using Core Profile
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL Test", nullptr, nullptr); // Create a window with specified width, height, and title
    if (!window) {
        std::cerr << "Failed to create window\n";
        glfwTerminate();
        return -1;
    }

	glfwMakeContextCurrent(window); // Tell GLFW to use the created window's context
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback); // Set the framebuffer size callback to adjust viewport on window resize (Can resize window)

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) { // Load OpenGL functions using GLAD
        std::cerr << "Failed to initialize GLAD\n";
        return -1;
    }

	glViewport(0, 0, 800, 600); // Set the initial viewport size


    unsigned int triangleVAO = createTriangleVAO(vertices, sizeof(vertices));
	unsigned int shaderProgram = createShaderProgram(vertexShaderSource, fragmentShaderSource);


	while (!glfwWindowShouldClose(window)) { // Main loop: run until the window should close
        // Render
        glClearColor(0.1f, 0.1f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Draw Triangle
        glUseProgram(shaderProgram);
        glBindVertexArray(triangleVAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);    // Display the rendered image (double buffering)
		glfwPollEvents();           // Poll for and process events (like keyboard and mouse input)
    }

    glDeleteVertexArrays(1, &triangleVAO);
    glDeleteBuffers(1, &triangleVAO);
    glDeleteProgram(shaderProgram);

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
