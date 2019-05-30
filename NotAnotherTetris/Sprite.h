#pragma once
#include <SDL.h>
#include <string>

using namespace std;

class Sprite {
public:
	Sprite();
	~Sprite();

	void free();												// Deallocates texture
	bool loadFromFile(string path, SDL_Renderer* renderer);		// Loads image at specified path
	void render(int x, int y, SDL_Renderer* renderer);			// Renders texture at given point

	int getWidth();						// Get image width
	int getHeight();					// Get image height
	
private:
	SDL_Texture* mTexture;

	int mWidth;
	int mHeight;
};
