

#include "SpriteSheet.h"

#include "Texture2D.h"


SpriteSheet::SpriteSheet(int tex, int texWidth, int texHeight, int spriteWidth, int spriteHeight, const Shader& shader)
    : tex(tex), texWidth(texWidth), texHeight(texHeight), spriteWidth(spriteWidth), spriteHeight(spriteHeight), shader(shader)
{
}


SpriteSheet::~SpriteSheet()
{
    glDeleteVertexArrays(1, &this->quadVAO);
}

void SpriteSheet::drawSpriteFromSheet(const Texture2D& texture, glm::vec2 pos, glm::vec2 size, float rotate, glm::vec3 color, int frameIndex)
{
    
    const float tw = float(spriteWidth) / texWidth;
    const float th = float(spriteHeight) / texHeight;
    const int numPerRow = texWidth / spriteWidth;
    const float tx = (frameIndex % numPerRow) * tw;
    const float ty = (frameIndex / numPerRow + 1) * th;
    /*const float texVerts[] = {
        tx, ty,
        tx + tw, ty,
        tx + tw, ty + th,
        tx, ty + th
    };*/
    // pos      // tex
    const float vertices[] = {
        pos.x, pos.y, tx, ty,
        pos.x + spriteWidth, pos.y, tx + tw, ty,
        pos.x + spriteWidth, pos.y + spriteHeight, tx + tw, ty + th,
        pos.x, pos.y + spriteHeight, tx, ty + th
    };

    unsigned int VBO;
    glGenVertexArrays(1, &this->quadVAO);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindVertexArray(this->quadVAO);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // ... Bind the texture, enable the proper arrays

 // prepare transformations
    this->shader.use();
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(pos, 0.0f));  // first translate (transformations are: scale happens first, then rotation, and then final translation happens; reversed order)

    model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f)); // move origin of rotation to center of quad
    model = glm::rotate(model, glm::radians(rotate), glm::vec3(0.0f, 0.0f, 1.0f)); // then rotate
    model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f)); // move origin back

    model = glm::scale(model, glm::vec3(size, 1.0f)); // last scale

    this->shader.setMatrix4("model", model);

    // render textured quad
    this->shader.setVector3f("spriteColor", color);

    glActiveTexture(GL_TEXTURE0);
    texture.bind();

    glBindVertexArray(this->quadVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}