#ifndef BASE_CHARACTER_H
#define BASE_CHARACTER_H

#include "raylib.h"

class BaseCharacter
{
public:
    BaseCharacter();
    Vector2 getWorldPos() { return worldPos; }
    void undoMovement();
    virtual Rectangle getCollisionRec();
    virtual void tick(float deltaTime);
    virtual Vector2 getScreenPos() = 0;
    bool getAlive(){ return alive;}
    void setAlive(bool isAlive) { alive = isAlive; }

protected:
    Texture2D texture{LoadTexture("characters/link.png")};
    Vector2 worldPos{};
    Vector2 worldPosLastFrame{};
    Vector2 velocity{};
    // animation variables
    float runningTime{};
    int frame{};
    int maxFrame{6};
    float updateTime{1.0 / 32.0f};
    int secondRow{0};
    float speed{4.0f};
    // which direction the character is facing
    int leftRight{1};
    // width and height of sprite
    float width;
    float height;
    float scale{4.0f};

private:
    bool alive{true};
};

#endif