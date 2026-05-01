#ifndef DEFINES_H
#define DEFINES_H

#include <stdint.h>

#include "raylib.h"

// A LITTLE NOTE FOR EVERYONE
// LIMIT OF 1 BYTE:  uint8_t  = 0 - 255 (INCLUSIVE)
// LIMIT OF 2 BYTES: uint16_t = 0 - 65,535 (INCLUSIVE)
// LIMIT OF 4 BYTES: uint32_t = 0 - 4,294,967,295 (INCLUSIVE)
// LIMIT OF 8 BYTES: uint64_t = 0 - 18,446,744,073,709,551,615 (INCLUSIVE)

#define MAX_LAZERS_COUNT 3
#define MAX_METEORS_COUNT 8
#define MAX_METEORS_TEXTURES 6

#define SHIP_RADIUS 0.8f
#define LAZER_RADIUS 0.2f
#define METEOR_RADIUS 1.8f

#define LAZER_METEOR_RADIUS_SUM  (LAZER_RADIUS + METEOR_RADIUS)
#define SHIP_METEOR_RADIUS_SUM   (SHIP_RADIUS  + METEOR_RADIUS)

#define LAZER_METEOR_DIST_SQ     (LAZER_METEOR_RADIUS_SUM * LAZER_METEOR_RADIUS_SUM)
#define SHIP_METEOR_DIST_SQ      (SHIP_METEOR_RADIUS_SUM  * SHIP_METEOR_RADIUS_SUM)

typedef enum {
    MENU = 0,
    STARTING,
    PLAYING,
    ENDING,
    OVER
} State;

extern const Vector3 SHOULDER_OFFSET;
extern const float CAMERA_GAP;

extern const uint16_t TARGET_FPS;
extern const uint16_t SCREEN_WIDTH;
extern const uint16_t SCREEN_HEIGHT;

extern const float MAX_VIEWABLE_X_INDEX;
extern const float MIN_VIEWABLE_X_INDEX;
extern const float MAX_VIEWABLE_Z_INDEX;
extern const float MIN_VIEWABLE_Z_INDEX;

extern const char GAME_NAME[];

#endif
