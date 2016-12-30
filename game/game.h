// Grayson Pike, 2016

#ifndef GAME_H
#define GAME_H

#include <stdbool.h>
#include "../graphics/sdl_boilerplate.h"
#include "../data_structure/linked_list.h"

// Global friction coefficient
#define FRICTION (1.0f)

struct node *blocks;

void game_init();
bool game_update();
void game_quit();

#endif