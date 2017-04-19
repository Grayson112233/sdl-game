#include "resources.h"
#include "graphics.h"

#include <iostream>

// STATIC MEMBERS

const std::string Resources::RES_DIR = "res/";

// PRIVATE HELPER FUNCTIONS

bool Resources::load_font(TTF_Font **font, std::string filename, int size) {

    // Concatenate filename to resource directory
    std::string filepath = std::string(RES_DIR) + "fonts/" + filename;
    *font = TTF_OpenFont(filepath.c_str(), size);
    if(*font == NULL) {
        printf("Error loading font: %s\n", TTF_GetError());
        return false;
    }
    return true;

}

bool Resources::load_texture(SDL_Texture **texture, std::string filename){

    // Assumes texture is not already created
    *texture = NULL;

    // Imagefile -> Surface -> Texture
    // Empty surface to begin with
    SDL_Surface *loaded_surface = NULL;

    // Concatenate filename to resource directory
    std::string filepath = std::string(RES_DIR) + "images/" + filename;

    // Load imagefile into surface
    loaded_surface = IMG_Load(filepath.c_str());
    if(loaded_surface == NULL) {
        printf("Error loading image: %s\n", SDL_GetError());
        return false;
    }

    // If successful, transfer the surface into the texture
    *texture = SDL_CreateTextureFromSurface(renderer, loaded_surface);
    if(texture == NULL) {
        printf("Unable to create texture from surface: %s\n", SDL_GetError());
    }
    // Mode BLEND allows for rendering with alpha channel changes even on PNGs
    // without an alpha channel
    SDL_SetTextureBlendMode(*texture, SDL_BLENDMODE_BLEND);

    // Free the temporary surface
    SDL_FreeSurface(loaded_surface);

    return true;

}

// PUBLIC FUNCTIONS

Resources::Resources(SDL_Renderer *renderer) {
	this->renderer = renderer;
}

void Resources::load_resources() {

	// FONTS
	fonts["inconsolata"] = NULL;
    load_font(&fonts["inconsolata"], "Inconsolata/Inconsolata-Regular.ttf", 18);

    // TEXTURES
    load_texture(&textures["ship1"][1], "ship1/ship1.png");
    load_texture(&textures["ship1_piece"][1], "ship1/ship1_piece1.png");
    load_texture(&textures["ship1_piece"][2], "ship1/ship1_piece2.png");
    load_texture(&textures["ship1_piece"][3], "ship1/ship1_piece3.png");
    load_texture(&textures["ship1_piece"][4], "ship1/ship1_piece4.png");

    load_texture(&textures["ship2"][1], "ship2/ship2.png");
    load_texture(&textures["ship2_piece"][1], "ship2/ship2_piece1.png");
    load_texture(&textures["ship2_piece"][2], "ship2/ship2_piece2.png");
    load_texture(&textures["ship2_piece"][3], "ship2/ship2_piece3.png");
    load_texture(&textures["ship2_piece"][4], "ship2/ship2_piece4.png");

    load_texture(&textures["missile1"][1], "missiles/missile1.png");
    load_texture(&textures["missile2"][1], "missiles/missile2.png");

    load_texture(&textures["particle"][1], "particles/particle1.png");
    load_texture(&textures["particle"][2], "particles/particle2.png");
    load_texture(&textures["particle"][3], "particles/particle3.png");

}

TTF_Font* Resources::get_font(std::string name) {
	return fonts[name];
}

SDL_Texture* Resources::get_texture(std::string name, int frame) {
    return textures[name][frame];
}

Resources::~Resources() {
    
    // Iterate through fonts and free them
    std::map<std::string, TTF_Font*>::iterator font_it;
    for(font_it = fonts.begin(); font_it != fonts.end(); font_it++) {
        TTF_CloseFont(font_it->second);
    }
    
    // Iterate through textures and free them
    std::map<std::string, std::map<int, SDL_Texture*> >::iterator frames;
    for(frames = textures.begin(); frames != textures.end(); frames++) {
        std::map<int, SDL_Texture*>::iterator frame;
        for(frame = frames->second.begin(); frame != frames->second.end(); frame++) {
            //SDL_DestroyTexture(frame->second);
            frame->second = NULL;
        }
    }
    
}