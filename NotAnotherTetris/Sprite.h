#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include "Rect.h"

class Sprite {
public:
	bool mEnabled = true;

	Sprite(int id, int layer, Rect* rect);
	~Sprite();

	void destroy();									// Deallocates texture
	void free();									// Deallocates texture
	void setTexture(SDL_Texture* newTexture);		// Sets texture
	void render(SDL_Renderer* renderer);			// Renders texture at given point

	bool operator > (const Sprite& other) const;
	bool operator < (const Sprite& other) const;

	int getWidth();						// Get image width
	int getHeight();					// Get image height
	int getLayer();
	void setLayer(int value);

	void print();
	
private:
	int mId;
	int mLayer;
	SDL_Texture* mTexture;
	Rect* rect;

	int mWidth;
	int mHeight;
};
