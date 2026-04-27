#ifndef DEFINES_H
#define DEFINES_H

#include <stdint.h>
#include "raylib.h"

// A LITTLE NOTE FOR EVERYONE
// LIMIT OF 1 BYTE:  uint8_t  = 0 - 255 (INCLUSIVE)
// LIMIT OF 2 BYTES: uint16_t = 0 - 65,535 (INCLUSIVE)
// LIMIT OF 4 BYTES: uint32_t = 0 - 4,294,967,295 (INCLUSIVE)
// LIMIT OF 8 BYTES: uint64_t = 0 - 18,446,744,073,709,551,615 (INCLUSIVE)

#define MAX_LAZERS_COUNT 20
#define MAX_METEORS_COUNT 30

typedef enum {
    MENU = 0,
    STARTING,
    PLAYING,
    ENDING, OVER
} State;

extern const Vector3 SHOULDER_OFFSET;
extern const float CAMERA_GAP;

extern const float SHIP_RADIUS;
extern const float LAZER_RADIUS;
extern const float METEOR_RADIUS;

extern const uint16_t TARGET_FPS;
extern const uint16_t SCREEN_WIDTH;
extern const uint16_t SCREEN_HEIGHT;

extern const char GAME_NAME[];

#endif
