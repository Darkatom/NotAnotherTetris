#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <vector>
#include "Rect.h"

class Collider {
public:
	Vector2d position;
	float rotation;
	float width, height;

	Collider();
	Collider(Vector2d newPosition, float newRotation = 0, float newWidth = 1, float newHeight = 1);
	~Collider();

	bool intersects(Collider other);
	bool contains(Vector2d point);
	bool containsAny(std::vector<Vector2d> points);
	bool containsAll(std::vector<Vector2d> points);
	
	std::vector<Vector2d> getPoints();

	void print();
	void draw(SDL_Color color);

private:
	

};
