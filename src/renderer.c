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

    // Order matters here too
    drawPlayableFloor();

    drawLazer();
    drawMeteor();
    drawSpaceship();

    EndMode3D();
}

void freeRenderer() {
    CloseWindow();
}

void drawPlayableFloor() {
    float minX = MIN_VIEWABLE_X_INDEX;
    float maxX = MAX_VIEWABLE_X_INDEX;

    float maxZ = spaceship.pos.z + 5.0f;
    float minZ = spaceship.pos.z - MIN_VIEWABLE_Z_INDEX;

    float y = -2.0f;
    float hazeSpread = 20.0f;

    BeginBlendMode(BLEND_ADDITIVE);

    rlDisableBackfaceCulling();

    rlBegin(RL_QUADS);

    rlColor4ub(255, 0, 0, 60);
    rlVertex3f(minX, y, minZ);
    rlVertex3f(minX, y, maxZ);
    rlVertex3f(maxX, y, maxZ);
    rlVertex3f(maxX, y, minZ);

    rlColor4ub(255, 0, 0, 0);
    rlVertex3f(minX - hazeSpread, y, minZ);
    rlVertex3f(minX - hazeSpread, y, maxZ);

    rlColor4ub(255, 0, 0, 60);
    rlVertex3f(minX, y, maxZ);
    rlVertex3f(minX, y, minZ);

    rlColor4ub(255, 0, 0, 60);
    rlVertex3f(maxX, y, minZ);
    rlVertex3f(maxX, y, maxZ);

    rlColor4ub(255, 0, 0, 0);
    rlVertex3f(maxX + hazeSpread, y, maxZ);
    rlVertex3f(maxX + hazeSpread, y, minZ);

    rlEnd();
    rlEnableBackfaceCulling();

    Vector3 leftStart = {minX, y + 0.05f, maxZ};
    Vector3 leftEnd = {minX, y + 0.05f, minZ};
    DrawCylinderEx(leftStart, leftEnd, 0.15f, 0.15f, 8, RED);

    Vector3 rightStart = {maxX, y + 0.05f, maxZ};
    Vector3 rightEnd = {maxX, y + 0.05f, minZ};
    DrawCylinderEx(rightStart, rightEnd, 0.15f, 0.15f, 8, RED);

    EndBlendMode();
}
