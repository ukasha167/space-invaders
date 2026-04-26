#ifndef LAZER_H
#define LAZER_H

#include "defines.h"
#include "raylib.h"

typedef struct {
    int scale;
    float speed;
    bool isActive;
    Vector3 pos;
} Lazer;

extern Lazer lazers[];

void initLazer();
void spawnLazer(Vector3 shipPos, float shipSpeed);
void updateLazer(const float dt);
void drawLazer();
void destroyLazer();

#endif
