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

Sprite* sprite;
Rect textRect;
Sprite* sprite2;
Rect textRect2;

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

	SDL_Color color = { 0,0,0 };
	SDL_Color color2 = { 255,0,0 };
	textRect = Rect(center.x, center.y);
	textRect2 = Rect(center.x + 5, center.y + 5);

	sprite = MediaManager.newSprite("img/a.png", 1, &textRect);
	sprite2 = MediaManager.newSprite("img/b.png", 2, &textRect2);

	SDL_Rect fillRect = { SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };

	while (!update()) {
		SDL_SetRenderDrawColor(MediaManager.mRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
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
	
	if (InputManager.getKeyDown(Key_Left)) {
		sprite->setLayer(1);
		sprite2->setLayer(2);
		MediaManager.print();
		MediaManager.sortLayers();
	}

	if (InputManager.getKeyDown(Key_Right)) {
		sprite->setLayer(2);
		sprite2->setLayer(1);
		MediaManager.print();
		MediaManager.sortLayers();
	}
	// Update game

	return false;
}

void quit() {
	MediaManager.quit();
	SDL_Quit();
}