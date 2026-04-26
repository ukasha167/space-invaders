#include "lazer.h"

static Model lazerModel;
Lazer lazers[MAX_LAZERS_COUNT];

void initLazer() {
    lazerModel = LoadModel("../assets/assets3D/models/laser.glb");
    for (int i = 0; i < MAX_LAZERS_COUNT; i++) {
        lazers[i].isActive = false;
        lazers[i].speed = 5.5f;
        lazers[i].scale = 1;
    }
}

void spawnLazer(Vector3 shipPos, float shipSpeed) {
    for (int i = 0; i < MAX_LAZERS_COUNT; i++) {
        if (lazers[i].isActive == false) {
            lazers[i].pos = shipPos;
            lazers[i].speed += shipSpeed;
            lazers[i].isActive = true;
            return;
        }
    }
}

void updateLazer(const float dt) {
    for (int i = 0; i < MAX_LAZERS_COUNT; i++) {
        if (lazers[i].isActive == true) {
            lazers[i].pos.z -= lazers[i].speed * dt;
        }
    }
}

void drawLazer() {
    for (int i = 0; i < MAX_LAZERS_COUNT; i++) {
        if (lazers[i].isActive == true) {
            DrawModel(lazerModel, lazers[i].pos, lazers[i].scale, WHITE);
        }
    }
}

void destroyLazer() { UnloadModel(lazerModel); }
