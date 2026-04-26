#include "renderer.h"

void renderSpaceship(const struct Spaceship *spaceship) {
    DrawModel(spaceship->model, spaceship->pos, spaceship->scale, WHITE);
}
