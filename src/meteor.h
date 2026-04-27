#ifndef METEOR_H
#define METEOR_H

#include "raylib.h"
#include "defines.h"
#include <stdbool.h>

typedef struct {
    float speed;
    float rotationAngle;
    Vector3 pos;
    Vector3 scale;
    Vector3 rotationAxis;
    bool isActive;
} Meteor;

extern Texture2D meteorTexture;
extern Meteor meteors[];

void initMeteor();
void loadMeteorModel();
void updateMeteor(const float dt);
void destroyMeteor();
void drawMeteor();
void freeMeteor();

#endif
