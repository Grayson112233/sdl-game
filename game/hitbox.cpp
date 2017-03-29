#include "hitbox.h"

// Size of rects drawn on corners by render_corners()
#define POINT_SIZE 6

Hitbox::Hitbox(float x_offset, float y_offset, int w, int h) {
	this->x_offset = x_offset;
	this->y_offset = y_offset;
	this->w = w;
	this->h = h;
}

void rotate_point(int *x, int *y, float angle) {
	*x = (*x) * cos(angle) - (*y) * sin(angle);
	*y = (*x) * sin(angle) + (*y) * cos(angle);
}

void Hitbox::update_pos(float x, float y, float angle) {
	// TODO: Account for offset center
	angle = -angle;
	// Apply offsets to new position
	this->x = x + x_offset;
	this->y = y + y_offset;
	// Set new angle
	this->angle = angle;
	// Calculate new corners

	// CENTER COORDS
	float cx = this->x + w / 2.0f;
	float cy = this->y + h / 2.0f;
	
	// BOTTOM RIGHT
	br.x = w/2;
	br.y = h/2;
	rotate_point(&br.x, &br.y, angle);
	br.x += cx;
	br.y += cy;

}

void Hitbox::render_corners(SDL_Renderer * renderer) {
	// Set draw color to white
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	// Create rectangles over each corner
	SDL_Rect tl_rect = { tl.x - POINT_SIZE / 2, tl.y - POINT_SIZE / 2, POINT_SIZE, POINT_SIZE };
	SDL_Rect tr_rect = { tr.x - POINT_SIZE / 2, tr.y - POINT_SIZE / 2, POINT_SIZE, POINT_SIZE };
	SDL_Rect bl_rect = { bl.x - POINT_SIZE / 2, bl.y - POINT_SIZE / 2, POINT_SIZE, POINT_SIZE };
	SDL_Rect br_rect = { br.x - POINT_SIZE / 2, br.y - POINT_SIZE / 2, POINT_SIZE, POINT_SIZE };
	// Draw rectangles
	SDL_RenderFillRect(renderer, &tl_rect);
	SDL_RenderFillRect(renderer, &tr_rect);
	SDL_RenderFillRect(renderer, &bl_rect);
	SDL_RenderFillRect(renderer, &br_rect);
}