#include "Collider.h"
#include <stdio.h>
#include "Media.h"

Collider::Collider() {
}

Collider::Collider(Vector2d newPosition, float newRotation, float newWidth, float newHeight) {
	position = newPosition;
	rotation = newRotation;
	width = newWidth;
	height = newHeight;
}

Collider::~Collider() {

}

bool Collider::intersects(Collider other) {	
	return containsAny(other.getPoints()) || other.containsAny(getPoints());;
}

bool Collider::contains(Vector2d point) {
	Vector2d delta = point - position;
	delta.rotate(-rotation);
	return (point.x >= position.x - width/2) 
		&& (point.x <= position.x + width/2)
		&& (point.y >= position.y - height/2)
		&& (point.y <= position.y + height/2);
}

bool Collider::containsAny(std::vector<Vector2d> points) {
	int i = 0;
	while (i < 4 && !contains(points[i])) {
		i++;
	}
	return i < 4;
}

bool Collider::containsAll(std::vector<Vector2d> points) {
	int i = 0;
	while (i < 4 && contains(points[i])) {
		i++;
	}
	return i >= 4;
}

std::vector<Vector2d> Collider::getPoints() {
	Vector2d A(-width / 2,-height / 2);
	Vector2d B(width / 2, -height / 2);
	Vector2d C(width / 2, height / 2);
	Vector2d D(-width / 2, height / 2);

	if (rotation != 0) {
		A.rotate(rotation);
		B.rotate(rotation);
		C.rotate(rotation);
		D.rotate(rotation);
	}

	std::vector<Vector2d> points{ position + A, position + B, position + C, position + D };
	return points;
}

void Collider::print() {
	printf("\n[Collider] Center: {%.2f, %.2f} - Rotation: %.2f - Size: [%.2f, %.2f]", position.x, position.y, rotation, width, height);
	printf("\n----> Corners:");
	std::vector<Vector2d> points = this->getPoints();
	points[0].print();
	points[1].print();
	points[2].print();
	points[3].print();
}

void Collider::draw(SDL_Color color) {
	std::vector<Vector2d> points = this->getPoints();

	SDL_SetRenderDrawColor(MediaManager.mRenderer, color.r, color.g, color.b, 0xFF);
	SDL_RenderDrawLine(MediaManager.mRenderer, points[0].x, points[0].y, points[1].x, points[1].y);
	SDL_RenderDrawLine(MediaManager.mRenderer, points[1].x, points[1].y, points[2].x, points[2].y);
	SDL_RenderDrawLine(MediaManager.mRenderer, points[2].x, points[2].y, points[3].x, points[3].y);
	SDL_RenderDrawLine(MediaManager.mRenderer, points[3].x, points[3].y, points[0].x, points[0].y);
	SDL_RenderPresent(MediaManager.mRenderer);
}