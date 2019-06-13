#include "Media.h"

Media MediaManager;	// Global media manager

Media::Media() {

}

Media::~Media() {
	destroyAllSprites();
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

void Media::destroyWindow() {
	SDL_DestroyRenderer(mRenderer);
	SDL_DestroyWindow(mWindow);
	mWindow = NULL;
	mRenderer = NULL;
}

bool Media::loadSprite(std::string path, Rect* rect) {
	SDL_Texture* texture;
	Sprite newSprite(rect);
	
	texture = getTexture(path);
	if (texture == nullptr) {
		texture = loadTexture(path);
		if (texture == nullptr) {
			printf("Failed to load texture image at %s!\n", path.c_str());
			return false;
		}
		textures.insert({ path, texture });
	}
		
	newSprite.setTexture(texture);
	mSprites.push_back(newSprite);
	return true;
}

SDL_Texture* Media::loadTexture(std::string path) {
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL) {
		printf("Unable to load %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
		SDL_FreeSurface(loadedSurface);
		return false;
	}

	//SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

	SDL_Texture* mTexture = SDL_CreateTextureFromSurface(mRenderer, loadedSurface);
	if (mTexture == NULL) {
		printf("Unable to create texture from %s! SDL_image Error: %s\n", path.c_str(), SDL_GetError());
		SDL_FreeSurface(loadedSurface);
		return false;
	}

	return mTexture;
}

SDL_Texture* Media::getTexture(std::string path) {
	std::map<std::string, SDL_Texture*>::iterator it = textures.find(path);
	SDL_Texture* texture;
	if (it != textures.end()) { //element found;		
		return it->second;
	}

	return nullptr;
}

void Media::destroyAllSprites() {
	for (size_t i = 0; i < mSprites.size(); i++) {
		mSprites[i].destroy();
	}
}

void Media::draw() {
	SDL_RenderClear(mRenderer);
	for (size_t i = 0; i < mSprites.size(); i++) {
		mSprites[i].render(mRenderer);
	}
	SDL_RenderPresent(mRenderer);
}

void Media::quit() {
	destroyAllSprites();
	MediaManager.destroyWindow();
	IMG_Quit();
}