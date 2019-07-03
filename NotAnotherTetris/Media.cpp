#include "Media.h"
#include <algorithm>

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

Sprite* Media::newSprite(std::string path, int layer, Rect* rect) {
	SDL_Texture* texture;
	
	texture = getTexture(path);
	if (texture == nullptr) {
		texture = loadTexture(path);
		if (texture == nullptr) {
			printf("Failed to load texture image at %s!\n", path.c_str());
			return nullptr;
		}
		textures.insert({ path, texture });
	}

	return newSprite(texture, layer, rect);
}

Sprite* Media::newText(std::string fontPath, std::string text, SDL_Color color, int layer, Rect* rect) {
	SDL_Texture* texture;

	std::string textKey = text + "_" + ((char)color.g) + ((char)color.b) + ((char)color.a);
	texture = getTexture(textKey.c_str());
	if (texture == nullptr) {
		texture = loadTextTexture(fontPath, text, color);
		if (texture == nullptr) {
			printf("Failed to load text sprite \"%s\"!\n", text.c_str());
			return nullptr;
		}
		textures.insert({ textKey, texture });
	}

	return newSprite(texture, layer, rect);
}

SDL_Texture* Media::loadTexture(std::string path) {
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL) {
		printf("Unable to load %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
		SDL_FreeSurface(loadedSurface);
		return false;
	}

	//SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

	SDL_Texture* texture = SDL_CreateTextureFromSurface(mRenderer, loadedSurface);
	if (texture == NULL) {
		printf("Unable to create texture from %s! SDL_image Error: %s\n", path.c_str(), SDL_GetError());
		SDL_FreeSurface(loadedSurface);
		return false;
	}

	return texture;
}

SDL_Texture* Media::loadTextTexture(std::string fontPath, std::string text, SDL_Color textColor) {
	TTF_Font *font = TTF_OpenFont(fontPath.c_str(), 28);
	if (font == NULL) {
		printf("Failed to load font! TTF Error: %s\n", TTF_GetError());
		return nullptr;
	}

	//Render text surface
	SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), textColor);
	if (textSurface == NULL) {
		printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
		SDL_FreeSurface(textSurface);
		return nullptr;
	}

	//Create texture from surface pixels
	SDL_Texture* texture = SDL_CreateTextureFromSurface(mRenderer, textSurface);
	if (texture == NULL) {
		printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
		SDL_FreeSurface(textSurface);
		return nullptr;
	}

	return texture;
}

SDL_Texture* Media::getTexture(std::string path) {
	std::map<std::string, SDL_Texture*>::iterator it = textures.find(path);
	SDL_Texture* texture;
	if (it != textures.end()) { //element found;		
		return it->second;
	}

	return nullptr;
}

Sprite* Media::newSprite(SDL_Texture* texture, int layer, Rect* rect) {
	Sprite newSprite(mSpriteCount++, layer, rect);
	newSprite.setTexture(texture);

	int position = getSortedPosition(newSprite.getLayer());	
	if (position > 0) {
		mSprites.insert(mSprites.begin(), position, newSprite);
	} else {
		mSprites.push_back(newSprite);
	}
	return &mSprites.back();
}

int Media::getSortedPosition(int layerValue) {
	std::list<Sprite>::iterator i, end;
	int count = 0;
	while (i != end && i->getLayer() < layerValue) {
		++i;
		count++;
	}
	return count;
}

void Media::sortLayers() {
	mSprites.sort([](const Sprite &a, const Sprite &b) { return a < b; });
}

void Media::destroyAllSprites() {
	std::list<Sprite>::iterator i, end;
	for (i = mSprites.begin(), end = mSprites.end(); i != end; ++i) {
		i->destroy();
	}
}

void Media::draw() {
	SDL_RenderClear(mRenderer);
	std::list<Sprite>::iterator i, end;
	for (i = mSprites.begin(), end = mSprites.end(); i != end; ++i) {
		i->render(mRenderer);
	}
	SDL_RenderPresent(mRenderer);
}

void Media::print() {
	std::list<Sprite>::iterator i, end;
	for (i = mSprites.begin(), end = mSprites.end(); i != end; ++i) {
		i->print();
	}
}

void Media::quit() {
	destroyAllSprites();
	MediaManager.destroyWindow();
	IMG_Quit();
}