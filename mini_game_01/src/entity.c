#include "../include/init.h"
#include "../include/entity.h"

void initEntity(Entity *e, int x, int y, int w, int h, Color c){
    e->pos.x = x ? x : 0;
    e->pos.y = y ? y : 0;
    e->w = w ? w : 16;
    e->h = h ? h : 16;
    e->c = c;
    e->points = 0;
}

void drawEntity(Entity *e){
    DrawRectangle(e->pos.x, e->pos.y, e->w, e->h, e->c);
}

void movePlayer(Entity *e, float speed){
    if ( state != 1){
        return;
    }

    e->speed = speed;

    if (IsKeyDown(KEY_LEFT) && e->pos.x > 0){
        e->pos.x -= e->speed;
    }else if (IsKeyDown(KEY_RIGHT) && e->pos.x < GetScreenWidth() - e->w){
        e->pos.x += e->speed;
    }

}

void updateRock(Entity *e){
    if ( state != 1){
        return;
    }

    float rnd_x;

    if (e->pos.y > GetScreenHeight()){
        rnd_x = (float)GetRandomValue( 0.0f, (float)( GetScreenWidth() - e->w ) );
        e->pos.x = rnd_x;
        e->pos.y = - e->h;
        e->rock_passed = 1;
    }else {
        e->pos.y += e->speed;
        e->rock_passed = 0;
    }
}
