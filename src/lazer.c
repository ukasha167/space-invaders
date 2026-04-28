#include "lazer.h"

static Model lazerModel;
Lazer lazers[MAX_LAZERS_COUNT];

void initLazer() {
    for (int i = 0; i < MAX_LAZERS_COUNT; i++) {
        lazers[i].isActive = false;
        lazers[i].speed = 0.0f;
        lazers[i].rotationAngle = 180.0f;
        lazers[i].rotationAxis = (Vector3){1.0f, 0.0f, 0.0f};
        lazers[i].scale = (Vector3){0.05f, 0.05f, 0.3f};
    }
}

void loadLazerModel() {
    lazerModel = LoadModel("../assets/assets3D/models/laser.glb");
}

void spawnLazer(Vector3 shipPos, float shipSpeed) {
    for (int i = 0; i < MAX_LAZERS_COUNT; i++) {
        if (lazers[i].isActive == false) {
            lazers[i].pos = shipPos;
            lazers[i].speed = 30.0f + shipSpeed;
            lazers[i].isActive = true;
            return;
        }
    }
}

void updateLazer(const float dt) {
    float outsideBoundary = spaceship.pos.z - MIN_VIEWABLE_Z_INDEX;

    for (int i = 0; i < MAX_LAZERS_COUNT; i++) {
        if (lazers[i].isActive == true) {
            lazers[i].pos.z -= lazers[i].speed * dt;

            if (lazers[i].pos.z < outsideBoundary) {
                lazers[i].isActive = false;
            }
        }
    }
}

void drawLazer() {
    for (int i = 0; i < MAX_LAZERS_COUNT; i++) {
        if (lazers[i].isActive == true) {
            DrawModelEx(lazerModel, lazers[i].pos, lazers[i].rotationAxis,
                        lazers[i].rotationAngle, lazers[i].scale, WHITE);
        }
    }
}

void freeLazer() { UnloadModel(lazerModel); }
