#include <SDL.h>
#include <stdio.h>
#include <string>
#include <cmath>

#include "Media.h"
#include "Input.h"
#include "Rect.h"
#include "Timer.h"
#include "Collider.h"

using namespace std;

const string APP_NAME = "Not Another Tetris";

// Settings
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_FPS = 60;
const int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;

Uint32 frameTimer = 0;

Collider box;

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

	Vector2d center(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	box = Collider(center, 0, 40, 40);
	box.print();

	SDL_Rect fillRect = { SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };

	while (!update()) {
		SDL_SetRenderDrawColor(MediaManager.mRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
		MediaManager.draw();

		SDL_Color color = { 255,0,0 };
		box.draw(color);
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

	frameTimer = SDL_GetTicks();
	printf("\nFrameTimer initialized.");	

	return true;
}

bool update() {
	float deltaTime = (float) (SDL_GetTicks() - frameTimer) / 1000.0f;
	frameTimer = SDL_GetTicks();

	InputManager.update();
	if (InputManager.mQuit) {
		return true;
	}

	if (InputManager.getKey(Left)) {
		box.rotation -= 1;
	}

	if (InputManager.getKey(Right)) {
		box.rotation += 1;
	}
	// Update game

	return false;
}

void quit() {
	MediaManager.quit();
	SDL_Quit();
}