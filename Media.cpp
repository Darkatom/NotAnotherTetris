#include "Media.h"


Media MediaManager;	// Global media manager

Media::Media() {

}

Media::~Media() {
	freeAllSprites();
}

bool Media::initWindow(std::string appName, int screenWidth, int screenHeight) {
	// Set texture filtering to linear
	if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
		printf("\nWarning: Linear texture filtering not enabled!");
	}
	printf("\nLinear texture filtering enabled.");

	// Create window
	mWindow = SDL_CreateWindow(appName.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenWidth, screenHeight, SDL_WINDOW_SHOWN);
	if (mWindow == NULL) {
		printf("\nWindow could not be created! SDL Error: %s\n", SDL_GetError());
		return false;
	}
	printf("\nWindow created.");

	//Create vsynced renderer for window
	mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (mRenderer == NULL) {
		printf("\nRenderer could not be created! SDL Error: %s\n", SDL_GetError());
		return false;
	}
	printf("\nRenderer created.");

	//Initialize renderer color
	SDL_SetRenderDrawColor(mRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	printf("\nRenderer color initialized.");

	return true;
}

void Media::destroyWindow() {
	SDL_DestroyRenderer(mRenderer);
	SDL_DestroyWindow(mWindow);
	mWindow = NULL;
	mRenderer = NULL;
}

bool Media::loadSprite(std::string path) {
	Sprite newSprite;
	
	if (!newSprite.loadFromFile(path, mRenderer)) {
		printf("Failed to load texture image at %s!\n", path.c_str());
		return false;
	}

	mSprites.push_back(newSprite);
	return true;
}

void Media::freeAllSprites() {
	for (size_t i = 0; i < mSprites.size(); i++) {
		mSprites[i].free();
	}
}

void Media::draw() {
	SDL_RenderClear(mRenderer);
	for (size_t i = 0; i < mSprites.size(); i++) {
		mSprites[i].render(0, 0, mRenderer);
	}
	SDL_RenderPresent(mRenderer);
}
