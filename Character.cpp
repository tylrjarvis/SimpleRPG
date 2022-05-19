#include "Character.h"
#include "raymath.h"

Character::Character()
{
    width = texture.width/12;
    height = texture.height/8;
}
void Character::setScreenPos(int winWidth, int winHeight)
{
    screenPos = {
        (float)winWidth / 2.0f - 3.0f * (0.5f * width),
        (float)winHeight / 2.0f - 3.0f * (0.5f * height)
    };
}

void Character::tick(float deltaTime)
{
    //store last known worldPos
    worldPosLastFrame = worldPos;

    // direction player wants to move
    Vector2 direction{};

    // move the player
    if (IsKeyDown(KEY_A))
        direction.x -= 1.0f;
    if (IsKeyDown(KEY_D))
        direction.x += 1.0f;
    if (IsKeyDown(KEY_W))
        direction.y -= 1.0f;
    if (IsKeyDown(KEY_S))
        direction.y += 1.0f;
    if (Vector2Length(direction) != 0.0f)
    {
        // set worldPos = worldPos + direction (we are moving the map not the character)
        worldPos = Vector2Add(worldPos, Vector2Scale(Vector2Normalize(direction), speed));
        if (direction.y < 0.0f)
            charDirection = 0; // up
        else if (direction.x > 0.0f)
            charDirection = 1; // right
        else if (direction.y > 0.0f)
            charDirection = 2; // down
        else
            charDirection = 3; // left
    }
    else
    {
        frame = 0;
    }

    // update animation frame
    runningTime += deltaTime;
    if (runningTime >= updateTime)
    {
        frame++;
        runningTime = 0.0f;
        if (frame > maxFrame)
        {
            frame = 0;
            secondRow = 0;
        }
        else if (frame > 11)
            secondRow = 1;
    }

    Rectangle source{frame * width, (4 * secondRow + charDirection) * height, width, height};
    Rectangle dest{screenPos.x, screenPos.y, 3.0f * width, 3.0f * height};
    DrawTexturePro(texture, source, dest, Vector2{}, 0.0f, WHITE);
}

void Character::undoMovement()
{
    worldPos = worldPosLastFrame;
}