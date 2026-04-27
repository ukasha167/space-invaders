#include "spaceship.h"
#include "raylib.h"

Spaceship spaceship;
static Model spaceshipModel;

void initSpaceship() {
    spaceship.pos = (Vector3){0.0f, 0.0f, 0.0f};
    spaceship.speed = 5.0f;
    spaceship.scale = 1;
}

void loadSpaceshipModel() {
    spaceshipModel = LoadModel("../assets/assets3D/models/ship.glb");
}

void updateSpaceship(const float dt) {
    if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) {
        spaceship.pos.x -= spaceship.speed * dt;
    } else if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) {
        spaceship.pos.x += spaceship.speed * dt;
    }

    spaceship.pos.z -= spaceship.speed * dt;
}

void drawSpaceship() {
    DrawModel(spaceshipModel, spaceship.pos, spaceship.scale, WHITE);
}

void freeShip() { UnloadModel(spaceshipModel); }
