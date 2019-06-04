#include "Rect.h"

Rect::Rect() {
	position = Vector2d();
	rotation = 0;
	scale = Vector2d();
}

Rect::Rect(float posX, float posY, float newRotation, float scaX, float scaY) {
	position = Vector2d(posX, posY);
	rotation = newRotation;
	scale = Vector2d(scaX, scaY);
}

Rect::~Rect() {}