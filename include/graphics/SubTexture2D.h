#pragma once
#include <glm/glm.hpp>
#include "Texture2D.h"

class SubTexture2D {
public:
    SubTexture2D(Texture2D* texture, const glm::vec2& min, const glm::vec2& max);

    static SubTexture2D CreateFromGrid(Texture2D* texture, const glm::ivec2& coords, const glm::ivec2& cellSize, const glm::ivec2& spriteSize = { 1, 1 });

    Texture2D* GetTexture() const { return m_Texture; }
    const glm::vec2* GetTexCoords() const { return m_TexCoords; }

private:
    Texture2D* m_Texture;
    glm::vec2 m_TexCoords[4];
};
