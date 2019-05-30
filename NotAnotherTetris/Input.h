#pragma once
#include <SDL.h>

enum KEY_CODE {
	Up, Down, Left, Right,
	Space, Escape, Return,
	LeftControl, RightControl,
	LeftShift, RightShift,
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
	void printState();

private:
	bool mKeyStates[_TotalKeys];
	bool mLastKeyStates[_TotalKeys];

	void processEvent(SDL_Event event);
};
extern Input InputManager;