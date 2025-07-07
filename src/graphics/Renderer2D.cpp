#include "\GameEngine\include\graphics\Renderer2D.h"
#include "\GameEngine\include\graphics\Shader.h"
#include <glad/glad.h>

Renderer2D::Renderer2D() {
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

    // position (3) + color (4) + uv (2) + useTexture (1) = 10 floats
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 10 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 10 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 10 * sizeof(float), (void*)(7 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, 10 * sizeof(float), (void*)(9 * sizeof(float)));
    glEnableVertexAttribArray(3);

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
    // Nothing here yet
}

// ✅ Colored quad
void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color) {
    float vertices[] = {
        // x, y, z     r, g, b, a     u, v     useTexture
        position.x, position.y, 0.0f,   color.r, color.g, color.b, color.a,   0.0f, 0.0f, 0.0f,
        position.x + size.x, position.y, 0.0f,  color.r, color.g, color.b, color.a,   1.0f, 0.0f, 0.0f,
        position.x + size.x, position.y + size.y, 0.0f, color.r, color.g, color.b, color.a, 1.0f, 1.0f, 0.0f,
        position.x, position.y + size.y, 0.0f,   color.r, color.g, color.b, color.a, 0.0f, 1.0f, 0.0f,
    };

    unsigned int indices[] = { 0, 1, 2, 2, 3, 0 };
    unsigned int EBO;
    glGenBuffers(1, &EBO);

    m_Shader->use();

    glBindVertexArray(m_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    glBindVertexArray(0);
    glDeleteBuffers(1, &EBO);
}

// ✅ Textured quad
void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, Texture2D& texture) {
    float vertices[] = {
        // pos                  color       uv            useTexture
        position.x, position.y, 0.0f,      1,1,1,1,     1.0f, 1.0f, 1.0f,
        position.x + size.x, position.y, 0.0f, 1,1,1,1, 0.0f, 1.0f, 1.0f,
        position.x + size.x, position.y + size.y, 0.0f, 1,1,1,1, 0.0f, 0.0f, 1.0f,
        position.x, position.y + size.y, 0.0f,         1,1,1,1, 1.0f, 0.0f, 1.0f,
    };


    unsigned int indices[] = { 0, 1, 2, 2, 3, 0 };
    unsigned int EBO;
    glGenBuffers(1, &EBO);

    texture.Bind(0);
    m_Shader->use();
    m_Shader->setInt("u_Texture", 0);

    glBindVertexArray(m_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    glBindVertexArray(0);
    glDeleteBuffers(1, &EBO);
}

void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, Texture2D& texture, const glm::vec2 texCoords[4]) {
    float vertices[] = {
        // x, y, z     r,g,b,a      u, v             useTexture
        position.x, position.y, 0.0f,     1,1,1,1,   texCoords[0].x, texCoords[0].y, 1.0f,
        position.x + size.x, position.y, 0.0f, 1,1,1,1, texCoords[1].x, texCoords[1].y, 1.0f,
        position.x + size.x, position.y + size.y, 0.0f, 1,1,1,1, texCoords[2].x, texCoords[2].y, 1.0f,
        position.x, position.y + size.y, 0.0f,       1,1,1,1, texCoords[3].x, texCoords[3].y, 1.0f,
    };

    unsigned int indices[] = { 0, 1, 2, 2, 3, 0 };
    unsigned int EBO;
    glGenBuffers(1, &EBO);

    texture.Bind(0);
    m_Shader->use();
    m_Shader->setInt("u_Texture", 0);

    glBindVertexArray(m_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    glBindVertexArray(0);
    glDeleteBuffers(1, &EBO);
}






