#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>

#include "Texture2D.h"
#include "SpriteRenderer.h"


// Container object for holding all state relevant for a single
// game object entity. Each object in the game likely needs the
// minimal of state as described within GameObject.
class GameObject
{
public:

    // constructor(s)
    GameObject();
    GameObject(glm::vec2 pos, glm::vec2 size, Texture2D sprite, glm::vec3 color = glm::vec3(1.0f), glm::vec2 velocity = glm::vec2(0.0f, 0.0f));
    // draw sprite
    virtual void draw(SpriteRenderer& renderer);

    // object state
    glm::vec2   position, size, velocity;
    glm::vec3   color;
    float       rotation;
    bool        isSolid;
    bool        destroyed;
    // render state
    Texture2D   sprite;
};

