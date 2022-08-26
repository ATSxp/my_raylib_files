#include <string.h>
#include "include/raylib.h"
#include "raymath.h"
#include "include/init.h"
#include "include/entity.h"

Entity player;
Entity rock;

void resetGame(){
    player.die = 0;
    player.points = 0;
    player.pos.x = (SCREEN_W - 64) * 0.5f;
    player.pos.y = 300;

    rock.pos.x = (float)GetRandomValue( 0.0f, (float)( SCREEN_W - 32 ) ); 
    rock.pos.y = -32;
    rock.speed = 10;
}

int main(void){
    InitWindow(SCREEN_W, SCREEN_H, "Mini-game-01");
    SetTargetFPS(60);

    initEntity(&player, (SCREEN_W - 64) / 2, 350, 64, 64, BLACK);

    initEntity(&rock, (float)GetRandomValue( 0.0f, (float)( SCREEN_W - 32 ) ), -32, 32, 32, GRAY);
    rock.speed = 10;

    int cur_points = 0;

    while (!WindowShouldClose()){
        if ( IsKeyPressed(KEY_F1) ){
            debug = ! debug;
        }

        if ( state == MENU_STATE ){
            if ( IsKeyPressed(KEY_Z) ){
                state = GAME_STATE;
            }

        }else if ( state == GAME_STATE ){
            Rectangle player_hit_box = {
                player.pos.x, player.pos.y, player.w, player.h
            };
            
            Rectangle rock_hit_box = {
                rock.pos.x, rock.pos.y, rock.w, rock.h
            };

            if ( rock.rock_passed ){
                player.points++;
            }

            switch ( player.points ) {
                case 5:
                    rock.speed = 20;
                case 10:
                    rock.speed = 30;
                case 20:
                    rock.speed = 40;
                case 50:
                    rock.speed = 50;
                default:
                    rock.speed = 10;
            }

            if ( CheckCollisionRecs(player_hit_box, rock_hit_box) ){
                player.die = 1;
                state = OVER_STATE;
                cur_points = player.points;
            }

            movePlayer(&player, 5);
            updateRock(&rock);

        }else if ( state == OVER_STATE ){
            if ( IsKeyPressed(KEY_Z) ){
                state = GAME_STATE;
                resetGame();
            }else if ( IsKeyPressed(KEY_SPACE) ){
                state = MENU_STATE;
                resetGame();
            }

        }


        BeginDrawing();
            
            if ( state == MENU_STATE) {
                ClearBackground(LIGHTGRAY);

                char *title = "Mini-Game";
                int scale_f = 32;
                int len = strlen(title);
                float center_x = ( SCREEN_W - ( len * scale_f ) ) * 0.5f;
                float rest_x = (SCREEN_W - center_x);

                DrawTextEx(
                            GetFontDefault(), title, 
                            (Vector2){ center_x + ( rest_x / 4.5f), 0 }, 32, 
                            1, RED
                        );

                DrawText("Play [Z]", 0, SCREEN_H / 3, 32, BLACK);
                DrawText("Exit [ESC]", 0, SCREEN_H / 2, 32, BLACK);
                
            }else if ( state == GAME_STATE ){
                ClearBackground(RAYWHITE);
                drawEntity(&player);
                drawEntity(&rock);

                DrawText(TextFormat("Points: %i", player.points), 0, 0, 16, BLACK);
            }else if ( state == OVER_STATE ){
                ClearBackground(BLUE);
                char *str = "Game Over";
                int scale_f = 32;
                int len = strlen(str);
                float center_x = ( SCREEN_W - ( len * scale_f ) ) * 0.5f;
                float rest_x = (SCREEN_W - center_x);

                DrawTextEx(
                            GetFontDefault(), str, 
                            (Vector2){ center_x + ( rest_x / 4.5f), ( SCREEN_H - 100 ) * 0.5f }, 32, 
                            1, RED
                        );

                DrawText("Restart [Z]", 0, SCREEN_H / 2, 32, BLACK);
                DrawText("Menu [SPACE-BAR]", 0, SCREEN_H / 1.5, 32, BLACK);
                DrawText(TextFormat("Total Points: %i", cur_points), 0, SCREEN_H - 24, 24, BLACK);
            }

            if ( debug ){
                DrawFPS(0, 0);
                DrawText(TextFormat("Player die: %i", player.die), 0, 16, 16, BLACK);
            }

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
