#ifndef SOLVER_H
#define SOLVER_H

#include "raylib.h"
#include "defines.h"

extern const Vector3 CAMERA_POSITION;

void updateCamera(Camera3D *camera, Vector3 targetPos);

#endif
