#pragma once
#include <SDL.h>
#include <string>
#include <vector>
#include "Sprite.h"

class Media {
public:
	SDL_Window* mWindow;			//The window we'll be rendering to
	SDL_Renderer* mRenderer;		//The window renderer

	Media();
	~Media();
	bool initWindow(std::string appName, int screenWidth, int screenHeight);
	void destroyWindow();

	bool loadSprite(std::string path);
	void freeAllSprites();

	void draw();

private:
	vector<Sprite> mSprites;

};
extern Media MediaManager;

