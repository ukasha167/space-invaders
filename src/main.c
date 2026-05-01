#include "raylib.h"

#include "renderer.h"
#include "solver.h"

int main() {
    initSolver();
    initRenderer();

    while (!WindowShouldClose()) {
        updateGame(GetFrameTime());
        renderGame();
    }

    freeRenderer();
}
