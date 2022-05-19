#include "raylib.h"
#include "raymath.h"
#include "Character.h"

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

    //create character
    Character character;
    character.setScreenPos(windowWidth, windowHeight);

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);
        // game logic begins

        mapPos = Vector2Scale(character.getWorldPos(), -1);
        // drawing map to screen
        DrawTextureEx(map, mapPos, 0.0f, mapScale, WHITE);

        //update character and draw
        character.tick(GetFrameTime());

        //checking map bounds
        if(character.getWorldPos().x < 0.0f ||
            character.getWorldPos().y < 0.0f ||
            character.getWorldPos().x + windowWidth > map.width * mapScale ||
            character.getWorldPos().y + windowHeight > map.height * mapScale)
        {
            character.undoMovement();
        }
        // game logic ends
        EndDrawing();
    }
    CloseWindow();
}