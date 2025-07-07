#include "\GameEngine\include\graphics\SubTexture2D.h"

SubTexture2D::SubTexture2D(Texture2D* texture, const glm::vec2& min, const glm::vec2& max)
    : m_Texture(texture) {
    m_TexCoords[0] = { min.x, min.y };  // bottom-left
    m_TexCoords[1] = { max.x, min.y };  // bottom-right
    m_TexCoords[2] = { max.x, max.y };  // top-right
    m_TexCoords[3] = { min.x, max.y };  // top-left
}

SubTexture2D SubTexture2D::CreateFromGrid(Texture2D* texture, const glm::ivec2& coords, const glm::ivec2& cellSize, const glm::ivec2& spriteSize) {
    glm::vec2 texSize = { texture->Width, texture->Height };

    glm::vec2 min = {
        (coords.x * cellSize.x) / texSize.x,
        (coords.y * cellSize.y) / texSize.y
    };

    glm::vec2 max = {
        ((coords.x + spriteSize.x) * cellSize.x) / texSize.x,
        ((coords.y + spriteSize.y) * cellSize.y) / texSize.y
    };

    return SubTexture2D(texture, min, max);
}
