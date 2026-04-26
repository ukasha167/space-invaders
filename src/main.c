#include "defines.h"
#include "raylib.h"

int main() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, GAME_NAME);

    Image icon = LoadImage("../assets/images/icon.png");
    ImageFormat(&icon, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8);

    SetWindowIcon(icon); // Supported only on Linux & Windows.
                         // (No MacOS. It doesn't have icons in title bar,
                         // So this line is ignored)
    UnloadImage(icon);

    Camera3D camera = {0};
    camera.position = (Vector3){5, 5, 10};
    camera.target = (Vector3){0, 0, 0};
    camera.up = (Vector3){0, 1, 0};
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    float dt;
    while (!WindowShouldClose()) {
        dt = GetFrameTime();

        BeginDrawing();
        ClearBackground(RAYWHITE);

        BeginMode3D(camera);

        DrawGrid(20, 1.0f);
        DrawCube((Vector3){0, 0.5f, 0}, 1, 1, 1, RED);
        DrawCubeWires((Vector3){0, 0.5f, 0}, 1, 1, 1, MAROON);

        EndMode3D();

        DrawFPS(10, 10);

        EndDrawing();
    }
    CloseWindow();
}
