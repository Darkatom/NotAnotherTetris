#pragma once
#include <SDL.h>
#include <string>
#include "Rect.h"

using namespace std;

class Sprite {
public:
	Sprite(Rect* rect);
	~Sprite();

	void destroy();												// Deallocates texture
	void free();												// Deallocates texture
	bool loadFromFile(string path, SDL_Renderer* renderer);		// Loads image at specified path
	void render(SDL_Renderer* renderer);			// Renders texture at given point

	int getWidth();						// Get image width
	int getHeight();					// Get image height
	
private:
	SDL_Texture* mTexture;
	Rect* rect;

	int mWidth;
	int mHeight;
};
