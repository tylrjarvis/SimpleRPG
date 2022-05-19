#include "raylib.h"
#include "raymath.h"
#include "Character.h"
#include "Prop.h"
#include "Enemy.h"
#include <string>

int main()
{
    const int windowWidth{384};
    const int windowHeight{384};
    InitWindow(windowWidth, windowHeight, "Tyler's Top Down RPG");

    // map texture
    Texture2D map = LoadTexture("nature_tileset/world_map.png");
    // map position
    Vector2 mapPos{0.0f, 0.0f};
    const float mapScale{4.0f};

    // create character
    Character character{windowWidth, windowHeight};

    // creates a prop
    Prop props[2]{
        Prop{Vector2{600.0f, 300.0f}, LoadTexture("nature_tileset/Rock.png")},
        Prop{Vector2{400.0f, 500.0f}, LoadTexture("nature_tileset/Log.png")}};

    Enemy goblin{
        Vector2{800.0f, 300.0f},
        LoadTexture("characters/goblin_idle_spritesheet.png"),
        LoadTexture("characters/goblin_run_spritesheet.png")};
    Enemy slime{
        Vector2{500.0f, 700.0f},
        LoadTexture("characters/slime_idle_spritesheet.png"),
        LoadTexture("characters/slime_run_spritesheet.png")};

    Enemy *enemies[]{
        &goblin,
        &slime};
    for (auto enemy : enemies)
    {
        enemy->setTarget(&character);
    }

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);
        // game logic begins

        mapPos = Vector2Scale(character.getWorldPos(), -1);
        // drawing map to screen
        DrawTextureEx(map, mapPos, 0.0f, mapScale, WHITE);

        // draw props on the map
        for (auto prop : props)
        {
            prop.Render(character.getWorldPos());
        }

        if (!character.getAlive()) // player not alive
        {
            DrawText("Game Over!", 55.0f, 45.0f, 40, RED);
            EndDrawing();
            continue;
        }
        else // player is alive
        {
            std::string characterHealth = "Health: ";
            characterHealth.append(std::to_string(character.getHealth()), 0, 5);
            DrawText(characterHealth.c_str(), 20.0f, 20.0f, 40, RED);
        }

        // update character and draw
        character.tick(GetFrameTime());

        // checking map bounds
        if (character.getWorldPos().x < 0.0f ||
            character.getWorldPos().y < 0.0f ||
            character.getWorldPos().x + windowWidth > map.width * mapScale ||
            character.getWorldPos().y + windowHeight > map.height * mapScale)
        {
            character.undoMovement();
        }

        // if character collides with props, don't move
        for (auto prop : props)
        {
            if (CheckCollisionRecs(
                    prop.getCollisionRec(character.getWorldPos()),
                    character.getCollisionRec()))
            {
                character.undoMovement();
            }
        }

        for (auto enemy : enemies)
        {
            enemy->tick(GetFrameTime());
        }
        // user is attacking
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            for (auto enemy : enemies)
            {
                // if weapon collision collides with enemy
                if (CheckCollisionRecs(enemy->getCollisionRec(), character.getWeaponCollisionRec()))
                {
                    enemy->setAlive(false);
                }
            }
        }
        // game logic ends
        EndDrawing();
    }
    CloseWindow();
}