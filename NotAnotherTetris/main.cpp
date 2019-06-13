#include <SDL.h>
#include <stdio.h>
#include <string>
#include <cmath>

#include "Media.h"
#include "Input.h"
#include "Rect.h"

using namespace std;

// Settings
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const string APP_NAME = "Not Another Tetris";
Rect helloRect(0, 0);
Rect doubleRect(0, 0);

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

	std:string imgPath = "img/hello_world.png";

	MediaManager.loadSprite(imgPath, &helloRect);
	MediaManager.loadSprite(imgPath, &doubleRect);

	doubleRect.scale.x = 0.5;
	doubleRect.scale.y = 0.5;

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
	
	return true;
}

bool update() {
	InputManager.update();
	if (InputManager.mQuit) {
		return true;
	}

	if (InputManager.getKeyDown(Down)) {
		helloRect.scale.x -= 0.1;
		helloRect.scale.y -= 0.1;
		helloRect.scale.x = helloRect.scale.x < 0.1 ? 0.1 : helloRect.scale.x;
		helloRect.scale.y = helloRect.scale.y < 0.1 ? 0.1 : helloRect.scale.y;
	}

	if (InputManager.getKeyDown(Up)) {
		helloRect.scale.x += 0.1;
		helloRect.scale.y += 0.1;
		helloRect.scale.x = helloRect.scale.x > 1 ? 1 : helloRect.scale.x;
		helloRect.scale.y = helloRect.scale.y > 1 ? 1 : helloRect.scale.y;
	}

	if (InputManager.getKey(Left)) {
		helloRect.rotation -= 0.1;
	}

	if (InputManager.getKey(Right)) {
		helloRect.rotation += 0.1;
	}
	// Update game

	return false;
}

void quit() {
	MediaManager.quit();
	SDL_Quit();
}