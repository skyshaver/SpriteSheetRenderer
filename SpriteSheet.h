#pragma once

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Shader.h"

class Texture2D;

class SpriteSheet
{
    int spriteWidth;
    int spriteHeight;
    int texWidth;
    int texHeight;

    int tex;

    unsigned int quadVAO;

    Shader shader;

public:
    SpriteSheet(int texWidth, int texHeight, int spriteWidth, int spriteHeight, const Shader& shader);
    ~SpriteSheet();

    void drawSpriteFromSheet(const Texture2D& texture, glm::vec2 pos, glm::vec2 size, float rotate, glm::vec3 color, int frameIndex);
};

