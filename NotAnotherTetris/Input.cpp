#include <SDL.h>
#include <string>
#include <bitset>
#include "Input.h"

Input InputManager;	// Global input manager

Input::Input() {

}

Input::~Input() {

}

#pragma region Control
void Input::update() {
	for (size_t i = 0; i < _TotalKeys; i++) {
		mKeyMemory[i] = mKeyStates[i];
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

	if (event.type != SDL_MOUSEBUTTONUP && event.type != SDL_MOUSEBUTTONDOWN) {
		return;
	}

	KEY_CODE code = _TotalKeys;
	switch (event.button.button) {
		case SDL_BUTTON_LEFT:
			code = Mouse_Left;
			break;
		case SDL_BUTTON_MIDDLE:
			code = Mouse_Middle;
			break;
		case SDL_BUTTON_RIGHT:
			code = Mouse_Right;
			break;
		case SDL_BUTTON_X1:
			code = Mouse_X1;
			break;
		case SDL_BUTTON_X2:
			code = Mouse_X2;
			break;
	}

	if (event.type == SDL_MOUSEBUTTONDOWN) {
		set(code);
	} else {
		clear(code);
	}
}

void Input::processKeyboardEvent(SDL_Event event) {
	if (event.type != SDL_KEYUP && event.type != SDL_KEYDOWN) {
		return;
	}

	SDL_Keycode keyEvent = event.key.keysym.sym;  
	KEY_CODE code = parse(keyEvent);
	if (code == _TotalKeys) {
		return;
	}

	if (event.type == SDL_KEYDOWN) {
		set(code);
	} else {
		clear(code);
	}
}
#pragma endregion

#pragma region Queries
bool Input::getKeyDown(KEY_CODE code) {
	return check(code) && !checkMemory(code);
}

bool Input::getKeyUp(KEY_CODE code) {
	return !check(code) && checkMemory(code);
}

bool Input::getKey(KEY_CODE code) {
	return check(code);
}

Vector2d Input::getMousePosition() {
	return mMousePosition;
}
#pragma endregion

#pragma region Bit Operations
void Input::set(int position) {
	mKeyStates[position] = true;
}

void Input::clear(int position) {
	mKeyStates[position] = false;
}

void Input::toggle(int position) {
	mKeyStates[position] = !mKeyStates[position];
}

bool Input::check(int position) {
	return mKeyStates[position];
}

bool Input::checkMemory(int position) {
	return mKeyMemory[position];
}

KEY_CODE Input::parse(SDL_Keycode code) {
	switch (code) {
		case SDLK_BACKSPACE:	return Key_Backspace;
		case SDLK_TAB:			return Key_Tab;
		case SDLK_CLEAR:		return Key_Clear;
		case SDLK_RETURN:		return Key_Return;
		case SDLK_PAUSE:		return Key_Pause;
		case SDLK_ESCAPE:		return Key_Escape;
		case SDLK_SPACE:		return Key_Space;
		case SDLK_EXCLAIM:		return Key_Exclaim;
		case SDLK_QUOTEDBL:		return Key_QuoteDBL;
		case SDLK_HASH:			return Key_Hash;
		case SDLK_DOLLAR:		return Key_Dollar;
		case SDLK_AMPERSAND:	return Key_Ampersand;
		case SDLK_QUOTE:		return Key_Quote;
		case SDLK_LEFTPAREN:	return Key_LeftParenthesis;
		case SDLK_RIGHTPAREN:	return Key_RightParenthesis;
		case SDLK_ASTERISK:		return Key_Asterisk;
		case SDLK_PLUS:			return Key_Plus;
		case SDLK_COMMA:		return Key_Comma;
		case SDLK_MINUS:		return Key_Minus;
		case SDLK_PERIOD:		return Key_Period;
		case SDLK_SLASH:		return Key_Slash;
		case SDLK_0:	return Key_0;
		case SDLK_1:	return Key_1;
		case SDLK_2:	return Key_2;
		case SDLK_3:	return Key_3;
		case SDLK_4:	return Key_4;
		case SDLK_5:	return Key_5;
		case SDLK_6:	return Key_6;
		case SDLK_7:	return Key_7;
		case SDLK_8:	return Key_8;
		case SDLK_9:	return Key_9;
		case SDLK_COLON:		return Key_Colon;
		case SDLK_SEMICOLON:	return Key_Semicolon;
		case SDLK_LESS:		return Key_Less;
		case SDLK_EQUALS:	return Key_Equals;
		case SDLK_GREATER:	return Key_Greater;
		case SDLK_QUESTION:	return Key_Question;
		case SDLK_AT:		return Key_At;
		case SDLK_LEFTBRACKET:	return Key_LeftBracket;
		case SDLK_BACKSLASH:	return Key_Backslash;
		case SDLK_RIGHTBRACKET:	return Key_RightBracket;
		case SDLK_CARET:		return Key_Caret;
		case SDLK_UNDERSCORE:	return Key_Underscore;
		case SDLK_BACKQUOTE:	return Key_Backquote;
		case SDLK_a:	return Key_A;
		case SDLK_b:	return Key_B;
		case SDLK_c:	return Key_C;
		case SDLK_d:	return Key_D;
		case SDLK_e:	return Key_E;
		case SDLK_f:	return Key_F;
		case SDLK_g:	return Key_G;
		case SDLK_h:	return Key_H;
		case SDLK_i:	return Key_I;
		case SDLK_j:	return Key_J;
		case SDLK_k:	return Key_K;
		case SDLK_l:	return Key_L;
		case SDLK_m:	return Key_M;
		case SDLK_n:	return Key_N;
		case SDLK_o:	return Key_O;
		case SDLK_p:	return Key_P;
		case SDLK_q:	return Key_Q;
		case SDLK_r:	return Key_R;
		case SDLK_s:	return Key_S;
		case SDLK_t:	return Key_T;
		case SDLK_u:	return Key_U;
		case SDLK_v:	return Key_V;
		case SDLK_w:	return Key_W;
		case SDLK_x:	return Key_X;
		case SDLK_y:	return Key_Y;
		case SDLK_z:	return Key_Z;
		case SDLK_KP_0:		return Key_NumPad0;
		case SDLK_KP_1:		return Key_NumPad1;
		case SDLK_KP_2:		return Key_NumPad2;
		case SDLK_KP_3:		return Key_NumPad3;
		case SDLK_KP_4:		return Key_NumPad4;
		case SDLK_KP_5:		return Key_NumPad5;
		case SDLK_KP_6:		return Key_NumPad6;
		case SDLK_KP_7:		return Key_NumPad7;
		case SDLK_KP_8:		return Key_NumPad8;
		case SDLK_KP_9:		return Key_NumPad9;
		case SDLK_KP_PERIOD:	return Key_NumPad_Period;
		case SDLK_KP_DIVIDE:	return Key_NumPad_Divide;
		case SDLK_KP_MULTIPLY:	return Key_NumPad_Multiply;
		case SDLK_KP_MINUS:		return Key_NumPad_Minus;
		case SDLK_KP_PLUS:		return Key_NumPad_Plus;
		case SDLK_KP_ENTER:		return Key_NumPad_Enter;
		case SDLK_KP_EQUALS:	return Key_NumPad_Equals;
		case SDLK_DELETE:		return Key_Delete;
		case SDLK_UP:		return Key_Up;
		case SDLK_DOWN:		return Key_Down;
		case SDLK_RIGHT:	return Key_Right;
		case SDLK_LEFT:		return Key_Left;
		case SDLK_INSERT:	return Key_Insert;
		case SDLK_HOME:		return Key_Home;
		case SDLK_END:		return Key_End;
		case SDLK_PAGEUP:	return Key_PageUp;
		case SDLK_PAGEDOWN:	return Key_PageDown;
		case SDLK_F1:	return Key_F1;
		case SDLK_F2:	return Key_F2;
		case SDLK_F3:	return Key_F3;
		case SDLK_F4:	return Key_F4;
		case SDLK_F5:	return Key_F5;
		case SDLK_F6:	return Key_F6;
		case SDLK_F7:	return Key_F7;
		case SDLK_F8:	return Key_F8;
		case SDLK_F9:	return Key_F9;
		case SDLK_F10:	return Key_F10;
		case SDLK_F11:	return Key_F11;
		case SDLK_F12:	return Key_F12;
		case SDLK_F13:	return Key_F13;
		case SDLK_F14:	return Key_F14;
		case SDLK_F15:	return Key_F15;
		case SDLK_NUMLOCKCLEAR:	return Key_NumLock;
		case SDLK_CAPSLOCK:		return Key_CapsLock;
		case SDLK_SCROLLLOCK:	return Key_ScrollLock;
		case SDLK_RSHIFT:	return Key_RightShift;
		case SDLK_LSHIFT:	return Key_LeftShift;
		case SDLK_RCTRL:	return Key_RightControl;
		case SDLK_LCTRL:	return Key_LeftControl;
		case SDLK_RALT:		return Key_RightAlt;
		case SDLK_LALT:		return Key_LeftAlt;
		case SDLK_MODE:		return Key_Mode;
		case SDLK_HELP:		return Key_Help;
		case SDLK_PRINTSCREEN:	return Key_Print;
		case SDLK_SYSREQ:		return Key_SysReq;
		case SDLK_MENU:			return Key_Menu;
		case SDLK_POWER:		return Key_Power;
	}
	return _TotalKeys;
}
#pragma endregion

#pragma region Debug
void Input::printState() {	
	printf("\n\n--------- Input Manager State ---------");
	printf("\nQuit? %d", mQuit);
	printf("\nLast States:");
	for (size_t i = 0; i < _TotalKeys; i++) {
		printf("%d", mKeyMemory[i]);
	}

	printf("\nCurrent States:");
	for (size_t i = 0; i < _TotalKeys; i++) {
		printf("%d", mKeyStates[i]);
	}
}
#pragma endregion