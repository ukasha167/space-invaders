#ifndef RENDERER_H
#define RENDERER_H

#include "raylib.h"

#include "lazer.h"
#include "spaceship.h"
#include "solver.h"

extern Camera3D camera;

void initRenderer();
void renderGame();
void destroyRenderer();

#endif
