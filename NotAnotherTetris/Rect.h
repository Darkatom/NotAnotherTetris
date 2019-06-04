#pragma once
#include "Vector2d.h"

class Rect {
public:
	Vector2d position;
	float rotation;
	Vector2d scale;

	Rect();
	Rect(float posX, float posY, float newRotation = 0, float scaX = 1, float scaY = 1);
	~Rect();


private:

};