#ifndef SOLVER_H
#define SOLVER_H

#include "raylib.h"

#include "defines.h"
#include "lazer.h"
#include "spaceship.h"

extern const Vector3 CAMERA_POSITION;
extern Camera3D camera;

void initSolver();
void updateCamera(Camera3D *camera, Vector3 targetPos);
void updateGame(const float dt);
void destroySolver();

#endif
