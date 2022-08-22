#include "include/raylib.h"
#include <stdio.h>

#define SCREEN_W (const int)(800) // screen width
#define SCREEN_H (const int)(450) // screen height

typedef struct Entity{
    Image img; 
    Texture2D sprite;
    Vector2 pos; 
    Camera2D camera;
}Entity;

// Make the entity
void InitEntity(Entity* e, int x, int y, char * sprite){
    e->pos.x = x;
    e->pos.y = y;
    e->img = LoadImage(sprite);

    ImageResize(&e->img, 32, 32);
    e->sprite = LoadTextureFromImage(e->img);

    e->camera.target = (Vector2){e->pos.x + 20.0f, e->pos.y + 20.0f};
    e->camera.offset = (Vector2){SCREEN_W / 2.0f, SCREEN_H / 2.0f};
    e->camera.rotation = 0.0f;
    e->camera.zoom = 1.0f;
}

// draw the entity
void DrawEntity(Entity* e){
    DrawTexture(e->sprite, e->pos.x, e->pos.y, WHITE);
}

// move the entity
void SetMoveEntity(Entity* e){
    if (IsKeyDown(KEY_UP)){
        e->pos.y -= 5;
    }else if (IsKeyDown(KEY_DOWN)){
        e->pos.y += 5;
        
    }

    if (IsKeyDown(KEY_LEFT)){
        e->pos.x -= 5;
    }else if (IsKeyDown(KEY_RIGHT)){
        e->pos.x += 5;
    }

}

Entity player; // created player

int main(void){
    InitWindow(SCREEN_W, SCREEN_H, "Movement");
    SetWindowState(FLAG_VSYNC_HINT);
    SetTargetFPS(60);

    InitEntity(&player, SCREEN_W / 2, SCREEN_H / 2, "assets/sprites/carrasco_imperial_token.png");
    SetTextureFilter(player.sprite, TEXTURE_FILTER_BILINEAR);

    int FPS;
    bool debug_is_on = false;

    Rectangle bg = {(SCREEN_W - 300) * 0.5f, (SCREEN_H - 300) * 0.5f, 300, 300};

    char * title_screen = "Teste de movimento e Camera 2D";
    int text_scale = 32;
    Vector2 text_size = MeasureTextEx(GetFontDefault(), title_screen, text_scale, 3.0f);

    int text_scale_datas = 16;

    while (!WindowShouldClose()){
        FPS = GetFPS();

        SetMoveEntity(&player);
        player.camera.target = (Vector2){player.pos.x + 20, player.pos.y + 20};


        if (IsKeyPressed(KEY_F1)){
            debug_is_on = ! debug_is_on;
        }

        BeginDrawing();
            ClearBackground(RAYWHITE);

            BeginMode2D(player.camera);
                DrawRectangleRec(bg, DARKGRAY);
                DrawEntity(&player);

                if (debug_is_on){
                    DrawLine((int)player.camera.target.x, -SCREEN_H * 10, (int)player.camera.target.x, SCREEN_H * 10, GREEN);
                    DrawLine(-SCREEN_W * 10, (int)player.camera.target.y, SCREEN_W * 10, (int)player.camera.target.y, GREEN);
                }

            EndMode2D();

            if (debug_is_on){
                DrawText(TextFormat("FPS: %i", FPS), 0, 0, text_scale_datas, BLACK);
                DrawText(TextFormat("X: %i", (int)player.pos.x), 0, text_scale_datas, text_scale_datas, BLACK);
                DrawText(TextFormat("Y: %i", (int)player.pos.y), 0, text_scale_datas * 2, text_scale_datas, BLACK);
                DrawText(TextFormat("Cam X: %i", (int)player.camera.target.x), 0, text_scale_datas * 3, text_scale_datas, BLACK);
                DrawText(TextFormat("Cam Y: %i", (int)player.camera.target.y), 0, text_scale_datas * 4, text_scale_datas, BLACK);
            }

            DrawText(title_screen, (SCREEN_W - text_size.x) / 2, SCREEN_H - text_size.y, text_scale, RED);
            
        EndDrawing();
    }

    UnloadTexture(player.sprite);
    CloseWindow();

    return 0;
}
