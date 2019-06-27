#pragma once
#include "Vector2d.h"
#include <math.h>
#include <stdio.h>

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

Vector2d Vector2d::operator - (const Vector2d& A) const {
	return Vector2d(x - A.x, y - A.y);
}

Vector2d Vector2d::operator - (const float A) const {
	return Vector2d(x - A, y - A);
}

Vector2d Vector2d::operator * (const float A) const {
	return Vector2d(x * A, y * A);
}

void Vector2d::rotate (const float angle) {
	float radians = angle * 0.01745;
	float aux = x * cos(radians) - y * sin(radians);
	y = x * sin(radians) + y * cos(radians);
	x = aux;
}

float Vector2d::Dot(const Vector2d& A) const {
	return A.x*x + A.y*y;
}

void Vector2d::print() {
	printf("\n[Vector] {%.2f, %.2f}", x, y);
}