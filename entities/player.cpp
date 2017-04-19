#include <math.h>
#include "player.h"
#include "missile.h"
#include "particle.h"
#include "ship_part.h"
#include "../debug.h"

// Time between firing missiles
#define MISSILE_DELAY 0.5f
// How many particles are spawned when the ship explodes
#define NUM_PARTICLES 40

// STATIC MEMBERS

const int Player::w = 36;
const int Player::h = 40;

// PRIVATE HELPER FUNCTIONS

float Player::get_center_x() {
    return x + w/2;
}

float Player::get_center_y() {
    return y + h/2;
}

void Player::shoot_missile() {

    if(missile_cooldown == 0) {
        missile_cooldown = MISSILE_DELAY;
        float speed = 500;
        entities->push_back(new Missile(x, y, speed, angle, player_num,
                            screen_w, screen_h));
    }

}

void Player::spawn_explosion() {

    for(int i = 0; i < NUM_PARTICLES; i++) {
        entities->push_back(new Particle(
            // Center coords on ship
            x + w/2.0f,
            y + h/2.0f,
            // Random vx and vy between -10 and 10
            ((float)rand()) / RAND_MAX * 40.0f - 20, 
            ((float)rand()) / RAND_MAX * 40.0f - 20,
            // Random lifetime between 2 and 4 seconds
            ((float)rand()) / RAND_MAX * 2.0f + 2,
            // Random type from 1 to 3
            (rand() % 3) + 1
            ));
    }

    // Create the 4 fragmented pieces of the ship
    for(int i = 1; i <= 4; i++) {
        entities->push_back(new ShipPart(
            // Center coords on ship
            x + w/2.0f,
            y + h/2.0f,
            // Random vx and vy between -10 and 10
            ((float)rand()) / RAND_MAX * 40.0f - 20, 
            ((float)rand()) / RAND_MAX * 40.0f - 20,
            // Random rot_speed between -30 and 30
            ((float)rand()) / RAND_MAX * 60.0f - 30,
            // Random lifetime between 3 and 4 seconds
            ((float)rand()) / RAND_MAX * 2.0f + 3,
            player_num,
            i
            ));
    }

}

// PUBLIC FUNCTIONS

Player::Player(float x, float y, int player_num, int screen_w, int screen_h,
               std::vector<Entity*> *entities) : Entity(x, y) {

    hitbox = new Hitbox(0, 0, w, h);
    vx = vy = 0.0f;
    turn_speed = 3.0f;
    linear_accel = 300.0f;
    max_speed = 300.0f;
    angle = 0;
    missile_cooldown = 0.0f;
    alive = true;
    this->player_num = player_num;
    this->screen_w = screen_w;
    this->screen_h = screen_h;
    this->entities = entities;

}

void Player::update(float delta) {

    // Apply change in x and y directions
    x += delta * vx;
    y += delta * vy;

    // Enforce speed limit
    if(vx > max_speed) {
        vx = max_speed;
    }
    if(vy > max_speed) {
        vy = max_speed;
    }
    if(vx < -max_speed) {
        vx = -max_speed;
    }
    if(vy < -max_speed) {
        vy = -max_speed;
    }

    // Check for going out of bounds
    if(this->get_center_x() < 0) {
        x = screen_w - w/2;
    } else if (this->get_center_x() > screen_w) {
        x = 0 - w/2;
    }
    if(this->get_center_y() < 0) {
        y = screen_h - h/2;
    } else if (this->get_center_y() > screen_h) {
        y = 0 - h/2;
    }

    // Timers
    if(missile_cooldown > 0) {
        missile_cooldown -= delta;
        if(missile_cooldown < 0) {
            missile_cooldown = 0;
        }
    }

    hitbox->update_pos(x, y, angle);

}

void Player::render(SDL_Renderer *renderer, Resources *resources, float delta) {
    
    #ifdef DEBUG_RENDER_HITBOX_CORNERS
    hitbox->render_corners(renderer);
    #endif

    SDL_Texture *texture;
    if(player_num == 1) {
        texture = resources->get_texture("ship1", 1);
    } else {
        texture = resources->get_texture("ship2", 1);
    }

    int texture_width, texture_height;
    SDL_QueryTexture(texture, NULL, NULL, &texture_width, &texture_height);
    SDL_Rect dst = {
        (int)x,
        (int)y,
        texture_width,
        texture_height
    };

    SDL_RenderCopyEx(renderer, texture, NULL, &dst, angle / M_PI * 180 + 90,
                     NULL, SDL_FLIP_NONE);

}


// TODO: Fix redundancy
void Player::handle_inputs(float delta, Inputs *inputs) {

    // PLAYER 1
    if(player_num == 1) {
        // Movement Controls
        if(inputs->is_key_down(KEY_P1_MOVE_UP)) {
            vx += delta * linear_accel * cos(angle);
            vy += delta * linear_accel * sin(angle);
        } else if (inputs->is_key_down(KEY_P1_MOVE_DOWN)) {
            vx -= delta * linear_accel * cos(angle);
            vy -= delta * linear_accel * sin(angle);
        }
        if(inputs->is_key_down(KEY_P1_MOVE_LEFT)) {
            angle -= delta * turn_speed;
        } else if (inputs->is_key_down(KEY_P1_MOVE_RIGHT)) {
            angle += delta * turn_speed;
        }
        // Shooting
        if(inputs->is_key_down(KEY_P1_FIRE_MISSILE)) {
            shoot_missile();
        }
    }

    // PLAYER 2
    if(player_num == 2) {
        // Movement Controls
        if(inputs->is_key_down(KEY_P2_MOVE_UP)) {
            vx += delta * linear_accel * cos(angle);
            vy += delta * linear_accel * sin(angle);
        } else if (inputs->is_key_down(KEY_P2_MOVE_DOWN)) {
            vx -= delta * linear_accel * cos(angle);
            vy -= delta * linear_accel * sin(angle);
        }
        if(inputs->is_key_down(KEY_P2_MOVE_LEFT)) {
            angle -= delta * turn_speed;
        } else if (inputs->is_key_down(KEY_P2_MOVE_RIGHT)) {
            angle += delta * turn_speed;
        }
        // Shooting
        if(inputs->is_key_down(KEY_P2_FIRE_MISSILE)) {
            shoot_missile();
        }
    }

}

bool Player::is_alive() {
    return alive;
}

const int Player::get_id() {
    return 0;
}

const bool Player::collides() {
    return true;
}

// Checks for collisions with Missiles
bool Player::does_collide(int id) {
    return id == 1;
}

void Player::collide_entity(Entity *entity) {
    switch(entity->get_id()) {
        case 1:
            // If colliding with a Missile, die when it's from another Player
            if(((Missile*)entity)->get_player_num() != player_num) {
                spawn_explosion();
                alive = false;
            }
            break;
        default:
            break;
    } 
}

int Player::get_player_num() {
    return player_num;
}