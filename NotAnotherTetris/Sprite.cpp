#include <SDL_image.h>
#include "Sprite.h"

Sprite::Sprite(Rect* newRect) {
	mTexture = NULL;
	rect = newRect;
	mWidth = 0;
	mHeight = 0;
}

Sprite::~Sprite() {
	free();
}

void Sprite::destroy() {
	if (mTexture == NULL) {
		return;
	}

	SDL_DestroyTexture(mTexture);
	mTexture = NULL;
	rect = nullptr;
	mWidth = 0;
	mHeight = 0;
}

void Sprite::free() {
	if (mTexture == NULL) {
		return;
	}

	mTexture = nullptr;
	rect = nullptr;
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

void Sprite::render(SDL_Renderer* renderer) {	
	SDL_Rect renderQuad = { 
		rect->position.x, 
		rect->position.y,
		rect->scale.x * mWidth,
		rect->scale.y * mHeight
	};
	
	if (SDL_RenderCopyEx(renderer, mTexture, NULL, &renderQuad, rect->rotation, NULL, SDL_FLIP_NONE) < 0) {
		printf("Image could not be rendered! SDL Error: %s\n", SDL_GetError());
	}
}

int Sprite::getWidth() {
	return mWidth;
}

int Sprite::getHeight() {
	return mHeight;
}