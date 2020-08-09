#include "Game.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Spriterenderer.h"
#include "SpriteSheet.h"


Game::Game(unsigned int width, unsigned int height) : state(GameState::GAME_ACTIVE), keys(), width(width), height(height)
{
}

Game::~Game()
{
}

void Game::init()
{

    // load shaders
    ResourceManager::loadShader("shaders/sprite.vert", "shaders/sprite.frag", nullptr, "sprite");

    // configure shaders
    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(this->width),
        static_cast<float>(this->height), 0.0f, -1.0f, 1.0f);
    ResourceManager::getShader("sprite").use().setInteger("image", 0);
    ResourceManager::getShader("sprite").setMatrix4("projection", projection);

    // load textures
    ResourceManager::loadTexture("textures/background.jpg", false, "background");
    ResourceManager::loadTexture("textures/sprites.png", true, "sprites");
 
    renderer = std::make_unique<SpriteRenderer>(ResourceManager::getShader("sprite"));
    spriteSheet = std::make_unique<SpriteSheet>(64, 16, 16, 16, 16, ResourceManager::getShader("sprite"));
}

void Game::processInput(float dt)
{
    //if (this->state == GameState::GAME_ACTIVE)
    //{
    //    float velocity = PLAYER_VELOCITY * dt;
    //    // move playerboard
    //    if (this->keys[GLFW_KEY_A])
    //    {
    //        if (player->position.x >= 0.0f)
    //        {
    //            player->position.x -= velocity;
    //            if (ball->stuck) { ball->position.x -= velocity; }
    //        }
    //    }
    //    if (this->keys[GLFW_KEY_D])
    //    {
    //        if (player->position.x <= this->width - player->size.x)
    //        {
    //            player->position.x += velocity;
    //            if (ball->stuck) { ball->position.x += velocity; }
    //        }
    //    }
    //    if (this->keys[GLFW_KEY_SPACE]) { ball->stuck = false; }
    //}
}

void Game::update(float dt)
{

    this->doCollisionsExist();
}

void Game::render()
{
    renderer->drawSprite(ResourceManager::getTexture("background"),
        glm::vec2(0.0f, 0.0f), glm::vec2(this->width, this->height), 0.0f
    );
    spriteSheet->drawSpriteFromSheet(ResourceManager::getTexture("sprites"), glm::vec2(0.f, 0.f), glm::vec2(10, 10), 0.f, glm::vec3(1.f), 1);
}





void Game::doCollisionsExist()
{
   
}

bool Game::checkCollision(GameObject& one, GameObject& two) const // AABB - AABB collision
{

    bool collisionX = one.position.x + one.size.x >= two.position.x && two.position.x + two.size.x >= one.position.x;
    bool collisionY = one.position.y + one.size.y >= two.position.y && two.position.y + two.size.y >= one.position.y;

    return collisionX && collisionY;
}



Direction Game::vectorDirection(glm::vec2 target)
{
    std::array<glm::vec2, 4> compass = {
        glm::vec2(0.0f, 1.0f),	// up
        glm::vec2(1.0f, 0.0f),	// right
        glm::vec2(0.0f, -1.0f),	// down
        glm::vec2(-1.0f, 0.0f)	// left
    };

    float max = 0.0f;
    unsigned int best_match = -1;

    for (unsigned int i = 0; i < compass.size(); i++)
    {
        float dot_product = glm::dot(glm::normalize(target), compass[i]);
        if (dot_product > max)
        {
            max = dot_product;
            best_match = i;
        }
    }
    return (Direction)best_match;
}


