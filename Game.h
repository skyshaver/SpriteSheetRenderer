#pragma once

#include <array>
#include <vector>
#include <tuple>
#include <memory>
#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>


enum class GameState
{
    GAME_ACTIVE,
    GAME_MENU,
    GAME_WIN
};

enum class Direction
{
    UP,
    RIGHT,
    DOWN,
    LEFT
};

struct Collision
{
    bool isCollision;
    Direction direction;
    glm::vec2 diffVec;
};

class GameObject;
class SpriteRenderer;
class SpriteSheet;

class Game
{
public:

    Game(unsigned int width, unsigned int height);
    ~Game();

    void init();
    // game loop
    void processInput(float dt);
    void update(float dt);
    void render();

    void doCollisionsExist();
    bool checkCollision(GameObject& one, GameObject& two) const; // axis-aligned bounding box

    Direction vectorDirection(glm::vec2 target);

    // game state
    GameState state;
    std::array<bool, 1024> keys; // used to pass key state between game object and glfw
    unsigned int width, height;

    std::unique_ptr<SpriteRenderer> renderer;
    std::unique_ptr<SpriteSheet> spriteSheet;


private:
    glm::vec2 startPlayerPos{ 0.f };
    glm::vec2 startBallPos{ 0.f };
    float shaketime = 0.f;
    unsigned int playerLives = 0;
};

