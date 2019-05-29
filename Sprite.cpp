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

	SDL_DestroyTexture(mTexture);
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
}

bool Sprite::loadFromFile(string path, SDL_Renderer* renderer) {
	SDL_Texture* newTexture = NULL;

	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL) {
		printf("Unable to load %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
		SDL_FreeSurface(loadedSurface);
		return false;
	}

	SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

	newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
	if (newTexture == NULL) {
		printf("Unable to create texture from %s! SDL_image Error: %s\n", path.c_str(), SDL_GetError());
		SDL_FreeSurface(loadedSurface);
		return false;
	}

	mWidth = loadedSurface->w;
	mHeight = loadedSurface->h;

	SDL_FreeSurface(loadedSurface);
	mTexture = newTexture;
	return mTexture != NULL;
}

void Sprite::render(int x, int y, SDL_Renderer* renderer) {
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };
	SDL_RenderCopy(renderer, mTexture, NULL, &renderQuad);
}

int Sprite::getWidth() {
	return mWidth;
}

int Sprite::getHeight() {
	return mHeight;
}