#ifndef ENTITY_H
#define ENTITY_H

#include "raylib.h" // Raylib file

typedef struct Entity{
    Vector2 pos; 
    int w;
    int h;
    Color c;
    float speed;
    int points;
    int die; 
    int rock_passed;
}Entity;

void initEntity(Entity *e, int x, int y, int w, int h, Color c);
void drawEntity(Entity *e);
void movePlayer(Entity *e, float speed);
void updateRock(Entity *e);

#endif
