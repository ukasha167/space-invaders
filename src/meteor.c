#include "meteor.h"

static Model meteorModel;
Texture2D meteorTexture;
Meteor meteors[MAX_METEORS_COUNT];

void initMeteor() {
    for (int i = 0; i < MAX_METEORS_COUNT; i++) {
        meteors[i].isActive = true;
        meteors[i].pos = (Vector3){(float)GetRandomValue(-20, 20), 0.0f,
                                   (float)GetRandomValue(-150, -50)};
        meteors[i].scale = (Vector3){1.0f, 1.0f, 1.0f};
        meteors[i].speed = (float)GetRandomValue(5, 15);
    }
}

void loadMeteorModel() {
    Mesh mesh = GenMeshSphere(2.0f, 8, 8);
    meteorModel = LoadModelFromMesh(mesh);

    meteorTexture = LoadTexture("../assets/assets3D/textures/red.png");
    meteorModel.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = meteorTexture;
}

void updateMeteor(const float dt) {
    for (int i = 0; i < MAX_METEORS_COUNT; i++) {
        if (!meteors[i].isActive) {
            continue;
        }

        meteors[i].pos.z += meteors[i].speed * dt;

        if (meteors[i].pos.z > 10.0f) {
            meteors[i].pos.z = -150.0f;
            meteors[i].pos.x = (float)GetRandomValue(-20, 20);
        }
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
