#include "meteor.h"

static Shader meteorShader;
static Model meteorModels[MAX_METEORS_TEXTURES];
static Texture2D meteorTextures[MAX_METEORS_TEXTURES];
static int shaderLocation;

Meteor meteors;

void initMeteor() {
    for (int i = 0; i < MAX_METEORS_COUNT; i++) {
        spawnMeteor(i);
    }
}

void spawnMeteor(const int idx) {
    meteors.pos[idx] = (Vector3){
        (float)GetRandomValue(MIN_VIEWABLE_X_INDEX, MAX_VIEWABLE_X_INDEX), 0.0f,
        (float)GetRandomValue(spaceship.pos.z - MIN_VIEWABLE_Z_INDEX / 1.5,
                              spaceship.pos.z - MIN_VIEWABLE_Z_INDEX)};

    meteors.rotationAxis[idx] = (Vector3){
            (float)GetRandomValue(-10, 10) / 10.0f,
            (float)GetRandomValue(-10, 10) / 10.0f,
            (float)GetRandomValue(-10, 10) / 10.0f
        };

    if (meteors.rotationAxis[idx].x == 0 && meteors.rotationAxis[idx].y == 0) {
        meteors.rotationAxis[idx].x = 1.0f;
    }

    meteors.rotationAngle[idx] = (float)GetRandomValue(0, 360);
    meteors.rotationSpeed[idx] = (float)GetRandomValue(20, 100);

    float size = (float)GetRandomValue(8, 12) / 10.0f;
    meteors.scale[idx] = (Vector3){ size, size, size };
    meteors.speed[idx] = (float)GetRandomValue(15, 25) + (2.0f - size) * 5.0f;
    meteors.isActive[idx] = true;
}

void loadMeteorModel() {
    Mesh mesh = GenMeshSphere(2.0f, 8, 8);

    const char TEXTURES[MAX_METEORS_TEXTURES][15] = {"red.png",    "green.png",
                                                     "light.png",  "orange.png",
                                                     "purple.png", "dark.png"};

    meteorShader = LoadShader(0, "../assets/assets3D/shaders/flash.fs");
    shaderLocation = GetShaderLocation(meteorShader, "flash");

    for (int i = 0; i < MAX_METEORS_TEXTURES; i++) {
        meteorModels[i] = LoadModelFromMesh(mesh);

        const char *path = TextFormat("../assets/assets3D/textures/%s", TEXTURES[i]);
        meteorTextures[i] = LoadTexture(path);

        meteorModels[i].materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = meteorTextures[i];
        meteorModels[i].materials[0].shader = meteorShader;
    }
}

void updateMeteor(const float dt) {
    float outsideBoundary = spaceship.pos.z + MAX_VIEWABLE_Z_INDEX;

    for (int i = 0; i < MAX_METEORS_COUNT; i++) {
        if (!meteors.isActive[i] || meteors.pos[i].z > outsideBoundary) {
            spawnMeteor(i);
            meteors.hitTimer[i] = 0.0f;
            continue;
        } else {
            meteors.rotationAngle[i] += meteors.rotationSpeed[i] * dt;
            meteors.pos[i].z += meteors.speed[i] * dt;
        }

        if (meteors.hitTimer[i] > 0) {
            meteors.hitTimer[i] -= dt;
            if (meteors.hitTimer[i] <= 0) {
                meteors.isActive[i] = false;
            }
        }
    }
}

void drawMeteor() {
    for (int i = 0; i < MAX_METEORS_COUNT; i++) {
        if (!meteors.isActive[i]) {
            continue;
        }
        float intensity = (meteors.hitTimer[i] > 0.0f) ? (meteors.hitTimer[i] * 10.0f) : 0.0f;

        float flashVector[2] = { intensity, 0.5f };
        SetShaderValue(meteorShader, shaderLocation, flashVector, SHADER_UNIFORM_VEC2);

        DrawModelEx(
            meteorModels[i % MAX_METEORS_TEXTURES],
            meteors.pos[i],
            meteors.rotationAxis[i],
            meteors.rotationAngle[i],
            meteors.scale[i],
            WHITE);
    }
}

void freeMeteor() {
    UnloadTexture(meteorTextures[0]);
    UnloadModel(meteorModels[0]);

    for (int i = 1; i < MAX_METEORS_TEXTURES; i++) {
        meteorModels[i].meshCount = 0;
        UnloadTexture(meteorTextures[i]);
        UnloadModel(meteorModels[i]);
    }

    UnloadShader(meteorShader);
}
