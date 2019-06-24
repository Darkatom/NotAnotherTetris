#pragma once

// http://www.flipcode.com/archives/Faster_Vector_Math_Using_Templates.shtml
class Vector2d {
public:
	float x, y;

	Vector2d();
	Vector2d(const float X, const float Y);
	Vector2d operator + (const Vector2d& A) const;
	Vector2d operator + (const float A) const;
	void rotate (const float angle);
	float Dot(const Vector2d& A) const;
	void print();
};