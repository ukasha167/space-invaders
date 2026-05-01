#include "renderer.h"

static Texture title;
static Texture play;
static Texture over;

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
    Image img;

    img = LoadImage("../assets/assets2D/images/menu-text.png");
    title = LoadTextureFromImage(img);
    UnloadImage(img);

    img = LoadImage("../assets/assets2D/images/play-text.png");
    play = LoadTextureFromImage(img);
    UnloadImage(img);

    img = LoadImage("../assets/assets2D/images/over-text.png");
    over = LoadTextureFromImage(img);
    UnloadImage(img);

    loadLazerModel();
    loadMeteorModel();
    loadSpaceshipModel();
}

void renderGame() {
    BeginDrawing();
    ClearBackground(BLACK);

    BeginMode3D(camera);

    drawLazer();
    drawMeteor();
    drawSpaceship();
    drawPlayableFloor();

    EndMode3D();

    switch (state) {
    case MENU:
        DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, Fade(BLACK, 0.6f));
        DrawTexture(title, (SCREEN_WIDTH >> 1) - (title.width >> 1), 20, WHITE);
        DrawTextureEx(play, (Vector2){(SCREEN_WIDTH >> 1) - ((int)(play.width * 0.5) >> 1), SCREEN_HEIGHT - 250}, 0.0f, 0.5f, WHITE);
        break;

    case OVER:
        DrawRectangleGradientV(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, Fade(BLACK, 0.8f), Fade(RED, 0.4f));
        DrawTexture(over, (SCREEN_WIDTH >> 1) - (over.width >> 1), 20, WHITE);
        DrawTextureEx(play, (Vector2){(SCREEN_WIDTH >> 1) - ((int)(play.width * 0.5) >> 1), SCREEN_HEIGHT - 250}, 0.0f, 0.5f, WHITE);
        DrawText(TextFormat("SCORE: %3d", score), SCREEN_WIDTH - 200, 10, 34, WHITE);
        break;

    case PLAYING:
        DrawText(TextFormat("SCORE: %3d", score), SCREEN_WIDTH - 200, 10, 34, Fade(RED, 0.8f));
        break;

    case STARTING:
    case ENDING:
        break;
    }

    DrawFPS(10, 10);
    EndDrawing();
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

void freeRenderer() {
    UnloadTexture(title);
    UnloadTexture(play);
    UnloadTexture(over);

    freeShip();
    freeLazer();
    freeMeteor();

    CloseWindow();
}
