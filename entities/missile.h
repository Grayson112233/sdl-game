#ifndef MISSILE_H
#define MISSILE_H

#include "../game/entity.h"
#include "../game/hitbox.h"
#include <string>

class Missile: public Entity {

    static const int w, h;
    // Speed in px/sec
    float speed;
    float angle;
    int screen_w, screen_h;
    float time_alive;
    int player_num;
    bool alive;

    float get_center_x();
    float get_center_y();

public:
    Missile(float x, float y, float speed, float angle, int player_num, int screen_w, int screen_h);
    void update(float delta);
    void render(SDL_Renderer *renderer, Resources *resources, float delta);
    bool is_alive();
    const int get_id();
    const bool collides();
    bool does_collide(int id);
    void collide_entity(Entity *entity);
    int get_player_num();
};

#endif