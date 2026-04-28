#ifndef SPACESHIP_H
#define SPACESHIP_H

#include "raylib.h"
#include "defines.h"
#include "raylib.h"

typedef struct {
    int scale;
    float speed;
    Vector3 pos;
} Spaceship;

extern Spaceship spaceship;

void initSpaceship();
void loadSpaceshipModel();
void updateSpaceship(const float dt);
void drawSpaceship();
void freeShip();

#endif
