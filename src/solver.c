#include "solver.h"

Camera3D camera;

void initSolver() {
    camera.up = (Vector3){0.0f, 1.0f, 0.0f};
    camera.fovy = 60.0f;
    camera.projection = CAMERA_PERSPECTIVE;
    camera.position = CAMERA_POSITION;

    resetGame();
}

void updateCamera(Camera3D *camera, Vector3 targetPos) {
    camera->position.z = targetPos.z + CAMERA_GAP;
    camera->target.z = targetPos.z - 5;
}

void updateGame(const float dt) {
    if (IsKeyPressed(KEY_SPACE)) {
        spawnLazer(spaceship.pos, spaceship.speed);
    }

    updateLazer(dt);
    updateMeteor(dt);
    updateSpaceship(dt);
    updateCamera(&camera, spaceship.pos);

    // If checkCollision returns true, the player hit a meteor
    if (checkCollision()) {
        resetGame();
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
                // Add "Fun" Factor: In the future, increment score here
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

/*
 If you want the camera to have some weight.
 void UpdateCinematicCamera(Camera3D* cam, Vector3 targetPos) {
     Vector3 desiredPos = {
         targetPos.x + SHOULDER_OFFSET.x,
         targetPos.y + SHOULDER_OFFSET.y,
         targetPos.z + SHOULDER_OFFSET.z
     };

     float smoothness = 0.1f; // 0.1f is the smoothness. Lower = more "lag",
 Higher = tighter. cam->position.x += (desiredPos.x - cam->position.x) *
 smoothness; cam->position.y += (desiredPos.y - cam->position.y) * smoothness;
     cam->position.z += (desiredPos.z - cam->position.z) * smoothness;

     cam->target = targetPos;
 }
*/
