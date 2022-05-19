#include "Character.h"
#include "raymath.h"

Character::Character(int winWidth, int winHeight) : windowWidth(winWidth),
                                                    windowHeight(winHeight)
{
    width = texture.width / 12;
    height = texture.height / 8;
    scale = 3.0f;
    maxFrame = 23;
}
Vector2 Character::getScreenPos()
{
    return Vector2{
        static_cast<float>(windowWidth) / 2.0f - scale * (0.5f * width),
        static_cast<float>(windowHeight) / 2.0f - scale * (0.5f * height)};
}

void Character::tick(float deltaTime)
{
    if(!getAlive()) return;

    BaseCharacter::tick(deltaTime);

    // move the player
    if (IsKeyDown(KEY_A))
        velocity.x -= 1.0f;
    if (IsKeyDown(KEY_D))
        velocity.x += 1.0f;
    if (IsKeyDown(KEY_W))
        velocity.y -= 1.0f;
    if (IsKeyDown(KEY_S))
        velocity.y += 1.0f;
    if (Vector2Length(velocity) != 0.0f)
    {
        // set worldPos = worldPos + direction (we are moving the map not the character)
        worldPos = Vector2Add(worldPos, Vector2Scale(Vector2Normalize(velocity), speed));
        if (velocity.y < 0.0f)
            charDirection = 0; // up
        else if (velocity.x > 0.0f)
        {
            charDirection = 1; // right
            leftRight = 1;
        }
        else if (velocity.y > 0.0f)
            charDirection = 2; // down
        else
        {
            charDirection = 3; // left
            leftRight = -1;
        }
    }
    else
    {
        frame = 0;
    }

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
    Vector2 origin{};
    Vector2 offset{};
    float rotation{};
    if (leftRight > 0.0f)
    {
        origin = {0.0f, weapon.height * scale};
        offset = {45.f, 75.f};
        weaponCollisionRec = {
            getScreenPos().x + offset.x,
            getScreenPos().y + offset.y - weapon.height * scale,
            weapon.width * scale,
            weapon.height * scale
        };
        IsMouseButtonDown(MOUSE_LEFT_BUTTON) ? rotation = 35.0f : rotation = 0.0f;
    }
    else
    {
        origin = {weapon.width * scale, weapon.height * scale};
        offset = {30.0f, 75.f};
        weaponCollisionRec = {
            getScreenPos().x + offset.x - weapon.width * scale,
            getScreenPos().y + offset.y - weapon.height * scale,
            weapon.width * scale,
            weapon.height * scale
        };
        IsMouseButtonDown(MOUSE_LEFT_BUTTON) ? rotation = -35.0f : rotation = 0.0f;
    }

    // draw sword
    Rectangle swordSource{0.0f, 0.0f, static_cast<float>(weapon.width) * leftRight, static_cast<float>(weapon.height)};
    Rectangle swordDest{getScreenPos().x + offset.x, getScreenPos().y + offset.y, weapon.width * scale, weapon.height * scale};
    DrawTexturePro(weapon, swordSource, swordDest, origin, rotation, WHITE);

    Rectangle source{frame * width, (4 * secondRow + charDirection) * height, width, height};
    Rectangle dest{getScreenPos().x, getScreenPos().y, scale * width, scale * height};
    DrawTexturePro(texture, source, dest, Vector2{}, 0.0f, WHITE);
}
Rectangle Character::getCollisionRec()
{
    return Rectangle{
        getScreenPos().x,
        getScreenPos().y + collisionBuffer,
        width * scale,
        height * scale - collisionBuffer};
}
void Character::takeDamage(float damage)
{
    health -= damage;
    if(health <= 0.0f)
    {
        setAlive(false);
    }
}