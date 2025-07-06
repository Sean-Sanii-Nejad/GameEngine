#include <memory>
#include "Shader.h"

class Renderer2D {
public:
    Renderer2D();
    ~Renderer2D();

    void Init();
    void Shutdown();

    void BeginScene(const glm::mat4& viewProj);
    void EndScene();

    void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);

private:
    unsigned int m_VAO = 0;
    unsigned int m_VBO = 0;

    std::unique_ptr<Shader> m_Shader;  // Add this
    glm::mat4 m_ViewProjection;        // To hold the matrix passed in BeginScene
};
