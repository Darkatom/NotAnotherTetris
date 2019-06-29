#include <SDL.h>
#include <string>
#include "Input.h"

Input InputManager;	// Global input manager

Input::Input() {

}

Input::~Input() {

}

void Input::update() {
	for (size_t i = 0; i < _TotalKeys; i++) {
		mLastKeyStates[i] = mKeyStates[i];
	}

	SDL_Event e;		// Event handler
	while (!mQuit && SDL_PollEvent(&e) != 0) {
		mQuit = (e.type == SDL_QUIT);
		processEvent(e);
	}
}

void Input::processEvent(SDL_Event event) {
	processKeyboardEvent(event);
	processMouseEvent(event);
}

void Input::processMouseEvent(SDL_Event event) {
	if (event.type == SDL_MOUSEMOTION) {
		mMousePosition.x = event.button.x;
		mMousePosition.y = event.button.y;
		return;
	}

	KEY_CODE index = _TotalKeys;
	switch (event.button.button) {
		case SDL_BUTTON_LEFT:
			index = MouseLeft;
			break;
		case SDL_BUTTON_MIDDLE:
			index = MouseMiddle;
			break;
		case SDL_BUTTON_RIGHT:
			index = MouseRight;
			break;
		case SDL_BUTTON_X1:
			index = MouseX1;
			break;
		case SDL_BUTTON_X2:
			index = MouseX2;
			break;
	}

	if (index == _TotalKeys) {
		return;
	}

	mKeyStates[index] = event.type == SDL_MOUSEBUTTONDOWN;
}

void Input::processKeyboardEvent(SDL_Event event) {
	KEY_CODE index = _TotalKeys;
	SDL_Keycode keyEvent = event.key.keysym.sym;
	if (keyEvent == SDLK_UP || keyEvent == SDLK_w) {
		index = Up;
	} else if (keyEvent == SDLK_DOWN || keyEvent == SDLK_s) {
		index = Down;
	} else if (keyEvent == SDLK_LEFT || keyEvent == SDLK_a) {
		index = Left;
	} else if (keyEvent == SDLK_RIGHT || keyEvent == SDLK_d) {
		index = Right;
	} else if (keyEvent == SDLK_SPACE) {
		index = Space;
	} else if (keyEvent == SDLK_RETURN) {
		index = Return;
	} else if (keyEvent == SDLK_ESCAPE) {
		index = Escape;
	} else if (keyEvent == SDLK_LCTRL) {
		index = LeftControl;
	} else if (keyEvent == SDLK_RCTRL) {
		index = RightControl;
	} else if (keyEvent == SDLK_LSHIFT) {
		index = LeftShift;
	} else if (keyEvent == SDLK_RSHIFT) {
		index = RightShift;
	}

	if (index == _TotalKeys) {
		return;
	}

	mKeyStates[index] = event.type == SDL_KEYDOWN;
}

bool Input::getKeyDown(KEY_CODE code) {
	return mKeyStates[code] && !mLastKeyStates[code];
}

bool Input::getKeyUp(KEY_CODE code) {
	return !mKeyStates[code] && mLastKeyStates[code];
}

bool Input::getKey(KEY_CODE code) {
	return mKeyStates[code];
}

Vector2d Input::getMousePosition() {
	return mMousePosition;
}

void Input::printState() {	
	printf("\n\n--------- Input Manager State ---------");
	printf("\nQuit? %d", mQuit);
	printf("\nLast States:\n");
	for (size_t i = 0; i < _TotalKeys; i++) {
		printf("%d", mLastKeyStates[i]);
	}

	printf("\nCurrent States:\n");
	for (size_t i = 0; i < _TotalKeys; i++) {
		printf("%d", mKeyStates[i]);
	}
}