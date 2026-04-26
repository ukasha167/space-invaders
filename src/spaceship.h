#ifndef SPACESHIP_H
#define SPACESHIP_H

#include "raylib.h"

struct Spaceship {
    int scale;
    float speed;
    Vector3 pos;

    Model model;
};

extern struct Spaceship spaceship;

void initSpaceship();
void updateSpaceship(const float dt);

#endif
