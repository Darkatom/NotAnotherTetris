#include "Sprite.h"

Sprite::Sprite(int id, int layer, Rect* newRect) {
	mId = id;
	mLayer = layer;
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

void Sprite::setTexture(SDL_Texture* newTexture) {
	free();	
	mTexture = newTexture;
	SDL_QueryTexture(mTexture, NULL, NULL, &mWidth, &mHeight);
}

void Sprite::render(SDL_Renderer* renderer) {	
	if (!mEnabled) {
		return;
	}

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

bool Sprite::operator > (const Sprite& other) const {
	return (mLayer > other.mLayer);
}

bool Sprite::operator < (const Sprite& other) const {
	return (mLayer < other.mLayer);
}

int Sprite::getWidth() {
	return mWidth;
}

int Sprite::getHeight() {
	return mHeight;
}

int Sprite::getLayer() {
	return mLayer;
}

void Sprite::setLayer(int value) {
	mLayer = value;
}

void Sprite::print() {
	printf("\n[Sprite] Id: %i - Layer: %i", mId, mLayer);
}
