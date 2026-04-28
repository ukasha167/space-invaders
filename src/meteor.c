#include "meteor.h"

static Model meteorModel;
Texture2D meteorTexture;
Meteor meteors[MAX_METEORS_COUNT];

void initMeteor() {
    for (int i = 0; i < MAX_METEORS_COUNT; i++) {
        spawnMeteor(i);
    }
}

void spawnMeteor(const int idx) {
    meteors[idx].pos = (Vector3){
        (float)GetRandomValue(MIN_VIEWABLE_X_INDEX, MAX_VIEWABLE_X_INDEX),
        0.0f, (float)GetRandomValue(spaceship.pos.z - MIN_VIEWABLE_Z_INDEX, spaceship.pos.z - MIN_VIEWABLE_Z_INDEX / 2 )};

    meteors[idx].speed = (float)GetRandomValue(5, 15);
    meteors[idx].scale = (Vector3){1.0f, 1.0f, 1.0f};
    meteors[idx].isActive = true;
}

void loadMeteorModel() {
    Mesh mesh = GenMeshSphere(2.0f, 8, 8);
    meteorModel = LoadModelFromMesh(mesh);

    meteorTexture = LoadTexture("../assets/assets3D/textures/red.png");
    meteorModel.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = meteorTexture;
}

void updateMeteor(const float dt) {
    float outsideBoundary = spaceship.pos.z + MAX_VIEWABLE_Z_INDEX;

    for (int i = 0; i < MAX_METEORS_COUNT; i++) {
        if (!meteors[i].isActive || meteors[i].pos.z > outsideBoundary) {
            spawnMeteor(i);
        }

        meteors[i].pos.z += meteors[i].speed * dt;
    }
}

void drawMeteor() {
    for (int i = 0; i < MAX_METEORS_COUNT; i++) {
        if (!meteors[i].isActive) {
            continue;
        }

        DrawModelEx(meteorModel, meteors[i].pos, (Vector3){0, 1, 0}, 0.0f,
                    meteors[i].scale, WHITE);
    }
}

void freeMeteor() {
    UnloadTexture(meteorTexture);
    UnloadModel(meteorModel);
}
