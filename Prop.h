#include "raylib.h"
class Prop
{
public:
    Prop(Vector2 pos, Texture2D tex);
    void Render(Vector2 characterPos);
    Rectangle getCollisionRec(Vector2 characterPos);
private:
    Vector2 worldPos{};
    Texture2D texture{};
    float scale{4.0f};
};