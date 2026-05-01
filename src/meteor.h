#ifndef METEOR_H
#define METEOR_H

#include <stdbool.h>
#include <string.h>

#include "raylib.h"
#include "spaceship.h"
#include "defines.h"

typedef struct {
    Vector3 pos[MAX_METEORS_COUNT];
    Vector3 scale[MAX_METEORS_COUNT];
    Vector3 rotationAxis[MAX_METEORS_COUNT];
    float speed[MAX_METEORS_COUNT];
    float rotationAngle[MAX_METEORS_COUNT];
    float rotationSpeed[MAX_METEORS_COUNT];
    float hitTimer[MAX_METEORS_COUNT];
    bool isActive[MAX_METEORS_COUNT];
} Meteor;

extern Meteor meteors;

void initMeteor();
void spawnMeteor(const int idx);
void loadMeteorModel();
void updateMeteor(const float dt);
void destroyMeteor();
void drawMeteor();
void freeMeteor();

#endif
