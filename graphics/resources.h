#ifndef RESOURCES_H
#define RESOURCES_H

#include <map>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

class Resources {

	static const std::string RES_DIR;
	std::map<std::string, TTF_Font*> fonts;
	std::map<std::string, SDL_Texture*> textures;
	bool load_font(TTF_Font **font, std::string filename, int size);
	SDL_Renderer *renderer;

public:
	Resources(SDL_Renderer *renderer);
	void load_resources();
	TTF_Font *get_font(std::string name);
	SDL_Texture *get_texture(std::string name);
	bool load_texture(SDL_Texture **texture, std::string filename);
	~Resources();

};

#endif