#include "raylib.h"

#include "defines.h"
#include "renderer.h"
#include "solver.h"
#include "spaceship.h"

int main() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, GAME_NAME);
    SetTargetFPS(TARGET_FPS);

    Image icon = LoadImage("../assets/assets2D/images/icon.png");
    ImageFormat(&icon, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8);

    SetWindowIcon(icon); // Supported only on Linux & Windows.
                         // (No MacOS. It doesn't have icons in title bar,
                         // So this line is ignored by the GLFW)
    UnloadImage(icon);

    Camera3D camera = {.up = (Vector3){0.0f, 1.0f, 0.0f},
                       .fovy = 60.0f,
                       .projection = CAMERA_PERSPECTIVE,
                       .position = CAMERA_POSITION};

    initSpaceship();

    float dt;
    while (!WindowShouldClose()) {
        dt = GetFrameTime();

        updateSpaceship(dt);
        updateCamera(&camera, spaceship.pos);

        BeginDrawing();
        ClearBackground(RAYWHITE);

        BeginMode3D(camera);

        DrawGrid(200, 1.0f);
        renderSpaceship(&spaceship);

        EndMode3D();

        DrawFPS(10, 10);

        EndDrawing();
    }
    CloseWindow();
}
