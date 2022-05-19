#include "BaseCharacter.h"

BaseCharacter::BaseCharacter()
{

}
void BaseCharacter::undoMovement()
{
    worldPos = worldPosLastFrame;
}

Rectangle BaseCharacter::getCollisionRec()
{
    return Rectangle{
        getScreenPos().x ,
        getScreenPos().y,
        width * scale,
        height * scale
    };
}
void BaseCharacter::tick(float deltaTime)
{
    worldPosLastFrame = worldPos;
    velocity = {};
    // update animation frame
    runningTime += deltaTime;
}
