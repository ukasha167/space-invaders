#ifndef DEFINES_H
#define DEFINES_H

#include <stdint.h>

// A LITTLE NOTE FOR EVERYONE
// LIMIT OF 1 BYTE:  uint8_t  = 0 - 255 (INCLUSIVE)
// LIMIT OF 2 BYTES: uint16_t = 0 - 65,535 (INCLUSIVE)
// LIMIT OF 4 BYTES: uint32_t = 0 - 4,294,967,295 (INCLUSIVE)
// LIMIT OF 8 BYTES: uint64_t = 0 - 18,446,744,073,709,551,615 (INCLUSIVE)

enum State : uint8_t {
    MENU = 0,
    STARTING,
    PLAYING,
    ENDING,
    OVER
};

const uint16_t SCREEN_WIDTH = 1000;
const uint16_t SCREEN_HEIGHT = 700;
const char *GAME_NAME = "Space Invaders";
const uint16_t TARGET_FPS = 62;

#endif
