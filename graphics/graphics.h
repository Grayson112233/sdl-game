#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <vector>

#include "resources.h"
#include "fps_counter.h"
#include "../game/entity.h"

class Graphics {

	static const int WIDTH, HEIGHT;

	FPSCounter fps_counter;

	Resources *resources;
	SDL_Window *window;
	SDL_Renderer *renderer;


	bool init_sdl();
	bool load_font_texture(SDL_Texture **texture, std::string font, std::string text, SDL_Color text_color);

public:
	Graphics();
	void render_fps();
	void clear_screen();
	void present_renderer(float delta);
	void render_entities(std::vector<Entity*> *entities, float delta);
	~Graphics();
};

#endif