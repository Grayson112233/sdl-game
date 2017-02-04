#include <SDL2/SDL.h>
#include "character.h"
#include "../graphics/sdl_boilerplate.h"

#define CHAR_WIDTH (64)
#define CHAR_HEIGHT (64)

#define CHAR_MAX_HEALTH (10)

struct character *create_character(float x, float y) {
    struct character *c = malloc(sizeof(struct character));
    c->block = create_block(x, y, CHAR_WIDTH, CHAR_HEIGHT);
    c->health = CHAR_MAX_HEALTH;
    return c;
}

void destroy_character(struct character *c) {
    free(c->block);
    free(c);
}

void draw_character(struct character *c) {
    draw_block(c->block);
}