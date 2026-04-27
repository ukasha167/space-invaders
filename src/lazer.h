#ifndef LAZER_H
#define LAZER_H

#include "defines.h"
#include "raylib.h"

typedef struct {
    float speed;
    float rotationAngle;
    Vector3 pos;
    Vector3 scale;
    Vector3 rotationAxis;
    bool isActive;
} Lazer;

extern Lazer lazers[];

void initLazer();
void loadLazerModel();
void spawnLazer(Vector3 shipPos, float shipSpeed);
void updateLazer(const float dt);
void drawLazer();
void freeLazer();

#endif
