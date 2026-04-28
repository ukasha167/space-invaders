#ifndef RENDERER_H
#define RENDERER_H

#include "raylib.h"

#include "lazer.h"
#include "meteor.h"
#include "solver.h"
#include "spaceship.h"

extern Camera3D camera;

void initRenderer();
void loadModels();
void renderGame();
void freeRenderer();
void DrawDebugBounds(float xMin, float xMax, float yMin, float yMax, float zMin,
                     float zMax, Color color);

#endif
