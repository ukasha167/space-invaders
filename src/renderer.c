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

    loadModels();
}

void loadModels() {
    loadLazerModel();
    loadMeteorModel();
    loadSpaceshipModel();
}

void renderGame() {
    BeginMode3D(camera);

    DrawGrid(500, 1.5f);
    drawSpaceship();
    drawLazer();
    drawMeteor();

    // DEBUG: Finding the playable area
    DrawDebugBounds(MIN_VIEWABLE_X_INDEX, MAX_VIEWABLE_X_INDEX, -5.0f, 15.0f,
                    spaceship.pos.z - MIN_VIEWABLE_X_INDEX,
                    spaceship.pos.z + MAX_VIEWABLE_Z_INDEX, RED);

    EndMode3D();
}

void freeRenderer() {
    CloseWindow();
}

void DrawDebugBounds(float xMin, float xMax, float yMin, float yMax, float zMin,
                     float zMax, Color color) {

    float width = xMax - xMin;
    float height = yMax - yMin;
    float length = zMax - zMin;

    Vector3 center = {(xMax + xMin) / 2.0f, (yMax + yMin) / 2.0f,
                      (zMax + zMin) / 2.0f};

    DrawCubeWires(center, width, height, length, color);
}
