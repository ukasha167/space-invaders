#include "defines.h"
#include "raylib.h"

int main() {
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, GAME_NAME);

  Image icon = LoadImage("../assets/images/icon.png");
  ImageFormat(&icon, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8);

  SetWindowIcon(icon); // Only Linux & Windows (No MacOS Because it doesn't have icons in title bar, So this line is ignored)
  UnloadImage(icon);

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(BLACK);

    EndDrawing();
  }
  CloseWindow();
}
