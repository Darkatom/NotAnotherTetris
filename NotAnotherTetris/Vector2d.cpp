#pragma once
#include "Vector2d.h"

Vector2d::Vector2d(void) {
	x = 0;
	y = 0;
}

Vector2d::Vector2d(const float X, const float Y) {
	x = X; y = Y;
}

Vector2d Vector2d::operator + (const Vector2d& A) const {
	return Vector2d(x + A.x, y + A.y);
}

Vector2d Vector2d::operator + (const float A) const {
	return Vector2d(x + A, y + A);
}

float Vector2d::Dot(const Vector2d& A) const {
	return A.x*x + A.y*y;
}