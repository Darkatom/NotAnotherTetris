#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>
#include <list>
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

	Sprite* newSprite(std::string path, int layer, Rect* rect);
	Sprite* newText(std::string fontPath, std::string text, SDL_Color color, int layer, Rect* rect);
	void sortLayers();
	void destroyAllSprites();

	void draw();
	void print();
	void quit();

private:
	int mSpriteCount;
	std::list<Sprite> mSprites;
	std::map<std::string, SDL_Texture*> textures;

	SDL_Texture* loadTexture(std::string path);
	SDL_Texture* loadTextTexture(std::string fontPath, std::string text, SDL_Color textColor);
	SDL_Texture* getTexture(std::string path);

	Sprite* newSprite(SDL_Texture* texture, int layer, Rect* rect);

	int getSortedPosition(int layerValue);
};
extern Media MediaManager;

