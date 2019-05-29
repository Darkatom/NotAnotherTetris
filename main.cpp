#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <string>
#include <cmath>

#include "Media.h"
#include "Input.h"

using namespace std;

// Settings
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const string APP_NAME = "Not Another Tetris";

bool init();		// Init app systems
bool update();		// Update frame logic
void quit();		// Free resources and close application


int main(int argc, char* args[]) {

	//Start up SDL and create window
	if (!init()) {
		printf("Failed to initialize!\n");
		SDL_Delay(2000);
		return -1;
	}

	MediaManager.loadSprite("img/hello_world.bmp");

	while (!update()) {
		MediaManager.draw();
	} 

	quit();

	return 0;
}

bool init() {
	printf("------------- INITIALIZING -------------");
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("\nSDL could not initialize! SDL Error: %s\n", SDL_GetError());
		return false;
	} 
	printf("\nSDL initialized.");

	if (!MediaManager.initWindow(APP_NAME, SCREEN_WIDTH, SCREEN_HEIGHT)) {
		printf("\nWindow could not initialize! SDL Error: %s\n", SDL_GetError());
		return false;
	}
	printf("\nWindow initialized.");

	//Initialize PNG loading
	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags)) {
		printf("\nSDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
		return false;
	}
	printf("\nSDL_image initialized.");

	//Initialize SDL_ttf
	if (TTF_Init() == -1) {
		printf("\nSDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
		return false;
	}
	printf("\nSDL_ttf initialized.");

	return true;
}

bool update() {
	InputManager.update();
	if (InputManager.mQuit) {
		return true;
	}

	// Update game

	return false;
}

void quit() {
	MediaManager.freeAllSprites();
	MediaManager.destroyWindow();

	IMG_Quit();
	SDL_Quit();
}