#include "renderer.h"

void initRenderer() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, GAME_NAME);
    SetTargetFPS(TARGET_FPS);

    Image icon = LoadImage("../assets/assets2D/images/icon.png");
    ImageFormat(&icon, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8);

    SetWindowIcon(icon); // Supported only on Linux & Windows.
                         // (No MacOS. It doesn't have icons in title bar,
                         // So this line is ignored by the GLFW)
    UnloadImage(icon);
}

void renderGame() {
    BeginMode3D(camera);

    DrawGrid(200, 1.0f);
    drawSpaceship();
    drawLazer();

    EndMode3D();
}

void destroyRenderer() {
    CloseWindow();
}
