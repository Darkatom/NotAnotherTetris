#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>
#include <vector>
#include <map>
#include <iterator> 
#include "Sprite.h"

class Media {
public:
	SDL_Window* mWindow;			//The window we'll be rendering to
	SDL_Renderer* mRenderer;		//The window renderer

	Media();
	~Media();
	bool initWindow(std::string appName, int screenWidth, int screenHeight);
	void destroyWindow();

	bool loadSprite(std::string path, Rect* rect);
	bool loadText(std::string fontPath, std::string text, SDL_Color color, Rect* rect);
	void destroyAllSprites();

	void draw();
	void quit();

private:
	std::vector<Sprite> mSprites;
	std::map<std::string, SDL_Texture*> textures;

	SDL_Texture* loadTexture(std::string path);
	SDL_Texture* loadTextTexture(std::string fontPath, std::string text, SDL_Color textColor);
	SDL_Texture* getTexture(std::string path);
};
extern Media MediaManager;

