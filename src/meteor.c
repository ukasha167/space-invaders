#include "meteor.h"

static Shader meteorShader;
static Model meteorModels[MAX_METEORS_TEXTURES];
static Texture2D meteorTextures[MAX_METEORS_TEXTURES];
static int shaderLocation;

Meteor meteors[MAX_METEORS_COUNT];

void initMeteor() {
    for (int i = 0; i < MAX_METEORS_COUNT; i++) {
        spawnMeteor(i);
    }
}

void spawnMeteor(const int idx) {
    meteors[idx].pos = (Vector3){
        (float)GetRandomValue(MIN_VIEWABLE_X_INDEX, MAX_VIEWABLE_X_INDEX), 0.0f,
        (float)GetRandomValue(spaceship.pos.z - MIN_VIEWABLE_Z_INDEX / 1.5,
                              spaceship.pos.z - MIN_VIEWABLE_Z_INDEX)};

    meteors[idx].speed = (float)GetRandomValue(15, 20);
    meteors[idx].scale = (Vector3){1.0f, 1.0f, 1.0f};
    meteors[idx].isActive = true;
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
        if (!meteors[i].isActive || meteors[i].pos.z > outsideBoundary) {
            spawnMeteor(i);
            meteors[i].hitTimer = 0.0f;
            continue;
        } else {
            meteors[i].pos.z += meteors[i].speed * dt;
        }

        if (meteors[i].hitTimer > 0) {
            meteors[i].hitTimer -= dt;
            if (meteors[i].hitTimer <= 0) {
                meteors[i].isActive = false;
            }
        }
    }
}

void drawMeteor() {
    for (int i = 0; i < MAX_METEORS_COUNT; i++) {
        if (!meteors[i].isActive) {
            continue;
        }
        float intensity = (meteors[i].hitTimer > 0.0f) ? (meteors[i].hitTimer * 10.0f) : 0.0f;

        float flashVector[2] = { intensity, 0.5f };
        SetShaderValue(meteorShader, shaderLocation, flashVector, SHADER_UNIFORM_VEC2);

        DrawModelEx(meteorModels[i % MAX_METEORS_TEXTURES], meteors[i].pos, (Vector3){0, 1, 0}, 0.0f, meteors[i].scale, WHITE);
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
