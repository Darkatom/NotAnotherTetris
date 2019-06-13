#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include "Rect.h"

class Sprite {
public:
	Sprite(Rect* rect);
	~Sprite();

	void destroy();									// Deallocates texture
	void free();									// Deallocates texture
	void setTexture(SDL_Texture* newTexture);		// Sets texture
	void render(SDL_Renderer* renderer);			// Renders texture at given point

	int getWidth();						// Get image width
	int getHeight();					// Get image height
	
private:
	SDL_Texture* mTexture;
	Rect* rect;

	int mWidth;
	int mHeight;
};
