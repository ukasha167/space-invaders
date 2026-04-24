#include "raylib.h"

int main() {
    InitWindow(1000, 1000, "Hello, World");

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);

        EndDrawing();
    }
    CloseWindow();
}
