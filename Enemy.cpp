#include "Enemy.h"
#include "raymath.h"
Enemy::Enemy(Vector2 pos, Texture2D idle_texture, Texture2D run_texture)
{
    worldPos = pos;
    texture = idle_texture;
    idle = idle_texture;
    run = run_texture;
    width = texture.width / maxFrame;
    height = texture.height;
    speed = 1.0f;
}
void Enemy::tick(float deltaTime)
{
    if(!getAlive()) return;

    BaseCharacter::tick(deltaTime);
    // get toTarget
    velocity = Vector2Subtract(target->getScreenPos(), getScreenPos());
    if(Vector2Length(velocity) < radius) velocity = {};
    // normalize vector to target
    velocity = Vector2Normalize(velocity);
    // scale toTarget by speed
    velocity = Vector2Scale(velocity, speed);
    // moveEnemy
    worldPos = Vector2Add(worldPos, velocity);

    if (Vector2Length(velocity) != 0.0f)
    {
        if (velocity.x < 0.0f)
            leftRight = -1; // up
        else
            leftRight = 1; // right
        texture = run;
    }
    else
    {
        texture = idle;
    }
    if (runningTime >= updateTime)
    {
        frame++;
        runningTime = 0.0f;
        if (frame > maxFrame)
        {
            frame = 0;
        }
    }

    Rectangle source{frame * width, 0.0f, leftRight * width, height};
    Rectangle dest{getScreenPos().x, getScreenPos().y, scale * width, scale * height};
    DrawTexturePro(texture, source, dest, Vector2{}, 0.0f, WHITE);

    if(CheckCollisionRecs(target->getCollisionRec(), getCollisionRec()))
    {
        target->takeDamage(damagePerSec * deltaTime);
    }
}

Vector2 Enemy::getScreenPos()
{
    return Vector2Subtract(worldPos, target->getWorldPos());
}