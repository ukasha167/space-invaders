#include "solver.h"

Camera3D camera;
State state = MENU;

void initSolver() {
    camera.up = (Vector3){0.0f, 1.0f, 0.0f};
    camera.fovy = 48.0f;
    camera.projection = CAMERA_PERSPECTIVE;
    camera.position = CAMERA_POSITION;

    SetRandomSeed(time(NULL));
}

void updateCamera(Vector3 targetPos) {
    camera.position.z = targetPos.z + CAMERA_GAP;
    camera.target.z = targetPos.z - 5;
}

void updateGame(const float dt) {
    switch (state) {

    case MENU:
        if (IsKeyPressed(KEY_SPACE)) {
            state = STARTING;
        }
        break;

    case STARTING:
        resetGame();
        if (1) {
            state = PLAYING;
        }
        break;

    case PLAYING:
        if (IsKeyPressed(KEY_SPACE)) {
            spawnLazer(spaceship.pos, spaceship.speed);
        }

        updateLazer(dt);
        updateMeteor(dt);
        updateSpaceship(dt);
        updateCamera(spaceship.pos);

        if (checkCollision()) {
            state = ENDING;
        }
        break;

    case ENDING:
        if (1) {
            state = OVER;
        }
        break;

    case OVER:
        if (IsKeyPressed(KEY_SPACE)) {
            state = STARTING;
        }
        break;
    }
}

bool checkCollision() {
    for (int i = 0; i < MAX_LAZERS_COUNT; i++) {
        if (!lazers[i].isActive) {
            continue;
        }

        for (int j = 0; j < MAX_METEORS_COUNT; j++) {
            if (!meteors[j].isActive) {
                continue;
            }
            if (CheckCollisionSpheres(lazers[i].pos, LAZER_RADIUS,
                                      meteors[j].pos, METEOR_RADIUS)) {
                lazers[i].isActive = false;
                meteors[j].isActive = false;
            }
        }
    }

    for (int j = 0; j < MAX_METEORS_COUNT; j++) {
        if (!meteors[j].isActive)
            continue;

        if (CheckCollisionSpheres(spaceship.pos, SHIP_RADIUS, meteors[j].pos,
                                  METEOR_RADIUS)) {
            return true;
        }
    }

    return false;
}

void freeSolver() {
    freeShip();
    freeLazer();
    freeMeteor();
}

void resetGame() {
    initLazer();
    initMeteor();
    initSpaceship();
}
