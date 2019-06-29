#pragma once
#include <SDL.h>
#include "Vector2d.h"

enum KEY_CODE {
	Up, Down, Left, Right,
	Space, Escape, Return,
	LeftControl, RightControl,
	LeftShift, RightShift,
	MouseLeft, MouseMiddle, MouseRight, MouseX1, MouseX2,
	_TotalKeys
};

class Input {
public:
	bool mQuit;

	Input();
	~Input();
	void update();
	bool getKeyDown(KEY_CODE code);
	bool getKeyUp(KEY_CODE code);
	bool getKey(KEY_CODE code);
	Vector2d getMousePosition();
	void printState();

private:
	bool mKeyStates[_TotalKeys];
	bool mLastKeyStates[_TotalKeys];
	Vector2d mMousePosition;

	void processEvent(SDL_Event event);
	void processMouseEvent(SDL_Event event);
	void processKeyboardEvent(SDL_Event event);
};
extern Input InputManager;