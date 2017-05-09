#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include "../game/entity.h"
#include "../game/hitbox.h"
#include "../input/inputs.h"

// The player's spaceship. Moves with velocity and rotation as given by
// inputs. Can shoot Missiles and die when hit by Missiles from other Players.
class Player: public Entity {

	// References
	std::vector<Entity*> *entities;

	// General Variables
	float vx, vy;
	float turn_speed, linear_accel;
	float max_speed;
	int player_num;
	float angle;
	float missile_cooldown;
	float laser_cooldown;
	bool alive;
	float time_alive;
	float invincible_time;

	// Helper Functions
	void shoot_missile();
	void shoot_laser();
	void spawn_explosion();

public:
	
	Player(float x, float y, int player_num, int screen_w, int screen_h,
		   std::vector<Entity*> *entities, float invincible_time=3.0f);
	void update(float delta);
	void render(SDL_Renderer *renderer, Resources *resources, float delta);
	void handle_inputs(float delta, Inputs *inputs);
	bool is_alive();
	const int get_id();
	const bool collides();
	bool does_collide(int id);
	void collide_entity(Entity *entity);
	int get_player_num();

};

#endif