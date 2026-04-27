#include "raylib.h"

#include "renderer.h"
#include "solver.h"

int main() {
    // Order Matters here because of the internal implementation of the Raylib
    initRenderer(); // First the Renderer
    initSolver(); // Then the Solver

    while (!WindowShouldClose()) {

        updateGame(GetFrameTime());

        BeginDrawing();
        ClearBackground(BLACK);

        renderGame();

        DrawFPS(10, 10);

        EndDrawing();
    }

    destroySolver();
    destroyRenderer();
}
