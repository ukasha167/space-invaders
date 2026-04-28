#include "defines.h"

const float CAMERA_GAP = 6.0f;
const Vector3 CAMERA_POSITION = (Vector3){-4.0f, 7.0f, CAMERA_GAP};

const uint16_t TARGET_FPS = 61;
const uint16_t SCREEN_WIDTH = 1660;
const uint16_t SCREEN_HEIGHT = 990;

const float SHIP_RADIUS = 0.8f;
const float LAZER_RADIUS = 0.2f;
const float METEOR_RADIUS = 1.8f;

// DEPENDENT ON THE CAMERA SETTINGS (DO NOT CHANGE)
const float MIN_VIEWABLE_X_INDEX = -6.5f; // From Origin
const float MAX_VIEWABLE_X_INDEX = 6.5f; // From Origin
const float MIN_VIEWABLE_Z_INDEX = 100.0f; // In-Front of the Spaceship's Position
const float MAX_VIEWABLE_Z_INDEX = 4.0f; // Behind the Spaceship's Position

const char GAME_NAME[] = "Space Invaders";
