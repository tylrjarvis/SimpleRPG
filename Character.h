#include "raylib.h"
class Character
{
public:
    Character();
    Vector2 getWorldPos() { return worldPos; }
    void setScreenPos(int winWidth, int winHeight);
    void tick(float deltaTime);
    void undoMovement();

private:
    Texture2D texture{LoadTexture("characters/link.png")};
    Vector2 screenPos{};
    Vector2 worldPos{};
    Vector2 worldPosLastFrame{};
    // animation variables
    float runningTime{};
    int frame{};
    int maxFrame{23};
    float updateTime{1.0 / 32.0f};
    int secondRow{0};
    float speed{4.0f};
    // which direction the character is facing
    int charDirection{1};
    //width and height of sprite
    float width;
    float height;
};