#ifndef METEOR_H
#define METEOR_H

#include <stdbool.h>
#include <string.h>

#include "raylib.h"
#include "spaceship.h"
#include "defines.h"

typedef struct {
    float speed;
    float rotationAngle;
    float hitTimer;
    Vector3 pos;
    Vector3 scale;
    Vector3 rotationAxis;
    bool isActive;
} Meteor;

extern Meteor meteors[];

void initMeteor();
void spawnMeteor(const int idx);
void loadMeteorModel();
void updateMeteor(const float dt);
void destroyMeteor();
void drawMeteor();
void freeMeteor();

#endif
