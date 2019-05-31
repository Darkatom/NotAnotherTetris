#include <SDL_image.h>
#include "Sprite.h"

Sprite::Sprite() {
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
}

Sprite::~Sprite() {
	free();
}

void Sprite::free() {
	if (mTexture == NULL) {
		return;
	}

	mTexture = nullptr;
	//SDL_DestroyTexture(mTexture);
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
}

bool Sprite::loadFromFile(string path, SDL_Renderer* renderer) {
	free();
	
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL) {
		printf("Unable to load %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
		SDL_FreeSurface(loadedSurface);
		return false;
	}

	//SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

	mTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
	if (mTexture == NULL) {
		printf("Unable to create texture from %s! SDL_image Error: %s\n", path.c_str(), SDL_GetError());
		SDL_FreeSurface(loadedSurface);
		return false;
	}

	mWidth = loadedSurface->w;
	mHeight = loadedSurface->h;

	SDL_FreeSurface(loadedSurface);
	return mTexture != NULL;
}

void Sprite::render(int x, int y, SDL_Renderer* renderer) {
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };
	if (SDL_RenderCopy(renderer, mTexture, NULL, &renderQuad) < 0) {
		printf("Image could not be rendered! SDL Error: %s\n", SDL_GetError());
	}
}

int Sprite::getWidth() {
	return mWidth;
}

int Sprite::getHeight() {
	return mHeight;
}