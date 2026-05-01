#include "lazer.h"

static Model lazerModel;
Lazer lazers;

void initLazer() {
    for (int i = 0; i < MAX_LAZERS_COUNT; i++) {
        lazers.isActive[i] = false;
        lazers.speed[i] = 0.0f;
        lazers.rotationAngle[i] = 180.0f;
        lazers.rotationAxis[i] = (Vector3){1.0f, 0.0f, 0.0f};
        lazers.scale[i] = (Vector3){0.05f, 0.05f, 0.3f};
    }
}

void loadLazerModel() {
    lazerModel = LoadModel("../assets/assets3D/models/laser.glb");
}

void spawnLazer(Vector3 shipPos, float shipSpeed) {
    for (int i = 0; i < MAX_LAZERS_COUNT; i++) {
        if (lazers.isActive[i] == false) {
            lazers.pos[i] = shipPos;
            lazers.speed[i] = 50.0f + shipSpeed;
            lazers.isActive[i] = true;
            return;
        }
    }
}

void updateLazer(const float dt) {
    float outsideBoundary = spaceship.pos.z - MIN_VIEWABLE_Z_INDEX;

    for (int i = 0; i < MAX_LAZERS_COUNT; i++) {
        if (lazers.isActive[i] == true) {
            lazers.pos[i].z -= lazers.speed[i] * dt;

            if (lazers.pos[i].z < outsideBoundary) {
                lazers.isActive[i] = false;
            }
        }
    }
}

void drawLazer() {
    for (int i = 0; i < MAX_LAZERS_COUNT; i++) {
        if (lazers.isActive[i] == true) {
            DrawModelEx(lazerModel, lazers.pos[i], lazers.rotationAxis[i],
                        lazers.rotationAngle[i], lazers.scale[i], WHITE);
        }
    }
}

void freeLazer() { UnloadModel(lazerModel); }
