#ifndef SPACESHIP_H
#define SPACESHIP_H

#include "raylib.h"
#include "defines.h"
#include "raylib.h"

typedef struct {
    Vector3 pos;
    float speed;
    int scale;
} Spaceship;

extern Spaceship spaceship;

void initSpaceship();
void loadSpaceshipModel();
void updateSpaceship(const float dt);
void drawSpaceship();
void freeShip();

#endif
