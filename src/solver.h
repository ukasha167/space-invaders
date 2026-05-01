#ifndef SOLVER_H
#define SOLVER_H

#include <time.h>
#include <string.h>

#include "raylib.h"
#include "lazer.h"
#include "meteor.h"
#include "defines.h"
#include "spaceship.h"

extern const Vector3 CAMERA_POSITION;
extern Camera3D camera;
extern State state;
extern int score;

void initSolver();
void updateCamera(Vector3 targetPos);
void updateGame(const float dt);
bool checkCollision();
void resetGame();
void freeSolver();

#endif
