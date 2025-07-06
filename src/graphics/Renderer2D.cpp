#include "\GameEngine\include\graphics\Renderer2D.h"
#include "\GameEngine\include\graphics\Shader.h"
#include <glad/glad.h>

Renderer2D::Renderer2D() {
    // Constructor can call Init or leave it explicit
    Init();
}

Renderer2D::~Renderer2D() {
    Shutdown();
}

void Renderer2D::Init() {
    glGenVertexArrays(1, &m_VAO);
    glGenBuffers(1, &m_VBO);

    glBindVertexArray(m_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

    // Setup vertex attributes (example: position + color)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    m_Shader = std::make_unique<Shader>("/GameEngine/shaders/triangle.vert", "/GameEngine/shaders/triangle.frag");
}

void Renderer2D::Shutdown() {
    glDeleteBuffers(1, &m_VBO);
    glDeleteVertexArrays(1, &m_VAO);
}

void Renderer2D::BeginScene(const glm::mat4& viewProj) {
    m_ViewProjection = viewProj;
    m_Shader->use();
    m_Shader->setMat4("u_ViewProjection", m_ViewProjection);
}


void Renderer2D::EndScene() {
    // Optional flush or unbind calls
}

void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color) {
    float vertices[] = {
        // positions           // colors (r,g,b,a)
        position.x, position.y, 0.0f,   color.r, color.g, color.b, color.a,
        position.x + size.x, position.y, 0.0f,   color.r, color.g, color.b, color.a,
        position.x + size.x, position.y + size.y, 0.0f,   color.r, color.g, color.b, color.a,
        position.x, position.y + size.y, 0.0f,   color.r, color.g, color.b, color.a,
    };

    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
    };

    unsigned int EBO;
    glGenBuffers(1, &EBO);

    glBindVertexArray(m_VAO);

    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    glBindVertexArray(0);

    glDeleteBuffers(1, &EBO);
}



