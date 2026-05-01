#ifndef LAZER_H
#define LAZER_H

#include "raylib.h"
#include "defines.h"
#include "spaceship.h"

typedef struct {
    Vector3 pos[MAX_LAZERS_COUNT];
    Vector3 scale[MAX_LAZERS_COUNT];
    Vector3 rotationAxis[MAX_LAZERS_COUNT];
    float speed[MAX_LAZERS_COUNT];
    float rotationAngle[MAX_LAZERS_COUNT];
    bool isActive[MAX_LAZERS_COUNT];
} Lazer;

extern Lazer lazers;

void initLazer();
void loadLazerModel();
void spawnLazer(Vector3 shipPos, float shipSpeed);
void updateLazer(const float dt);
void drawLazer();
void freeLazer();

#endif
