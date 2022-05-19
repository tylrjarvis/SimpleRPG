#ifndef CHARACTER_H
#define CHARACTER_H

#include "raylib.h"
#include "BaseCharacter.h"

class Character : public BaseCharacter
{
public:
    Character(int winWidth, int winHeight);
    virtual void tick(float deltaTime) override;
    virtual Rectangle getCollisionRec() override;
    virtual Vector2 getScreenPos() override;
    Rectangle getWeaponCollisionRec(){ return weaponCollisionRec; }
    float getHealth() const { return health; }
    void takeDamage(float damage);
private:
    int collisionBuffer = 50;
    int windowWidth{};
    int windowHeight{};
    int charDirection{1};
    Texture2D weapon{LoadTexture("characters/weapon_sword.png")};
    Rectangle weaponCollisionRec{};
    float health{100.0f};
};

#endif