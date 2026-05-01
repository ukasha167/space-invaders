#include "solver.h"

Camera3D camera;
State state = MENU;
int score = 0;

void initSolver() {
    camera.up = (Vector3){0.0f, 1.0f, 0.0f};
    camera.fovy = 48.0f;
    camera.projection = CAMERA_PERSPECTIVE;
    camera.position = CAMERA_POSITION;
    camera.target.z = -5.0f;

    SetRandomSeed(time(NULL));
    resetGame();
}

void updateCamera(Vector3 targetPos) {
    camera.position.z = targetPos.z + CAMERA_GAP;
    camera.target.z = targetPos.z - 5.0f;
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

bool checkCollision(void) {
    for (int i = 0; i < MAX_LAZERS_COUNT; i++) {
        if (!lazers.isActive[i]) {
            continue;
        }

        for (int j = 0; j < MAX_METEORS_COUNT; j++) {
            if (!meteors.isActive[j] || meteors.hitTimer[j] > 0.0f) {
                continue;
            }

            if (collisionOccured(lazers.pos[i], meteors.pos[j], LAZER_METEOR_DIST_SQ)) {
                lazers.isActive[i] = false;
                meteors.hitTimer[j] = 0.20f;
                score++;
                break;
            }
        }
    }

    for (int j = 0; j < MAX_METEORS_COUNT; j++) {
        if (!meteors.isActive[j] || meteors.hitTimer[j] > 0.0f) {
            continue;
        }

        if (collisionOccured(spaceship.pos, meteors.pos[j], SHIP_METEOR_DIST_SQ)) {
            return true;
        }
    }

    return false;
}

bool collisionOccured(Vector3 a, Vector3 b, float radiiSq) {
    float dx = a.x - b.x;
    float dy = a.z - b.z;

    return (dx * dx + dy * dy) <= radiiSq;
}

void freeSolver() {}

void resetGame() {
    initLazer();
    initMeteor();
    initSpaceship();
    score = 0;
}
