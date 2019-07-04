#pragma once
#include <SDL.h>
#include <vector>
#include "Vector2d.h"

enum KEY_CODE {
	Mouse_Left, Mouse_Middle, Mouse_Right, Mouse_X1, Mouse_X2,
	Key_Backspace, Key_Tab, Key_Clear, Key_Return, Key_Pause, Key_Escape, Key_Space, 
	Key_Exclaim, Key_QuoteDBL, Key_Hash, Key_Dollar, Key_Ampersand, Key_Quote, Key_LeftParenthesis, Key_RightParenthesis, Key_Asterisk,
	Key_Plus, Key_Comma, Key_Minus, Key_Period, Key_Slash,
	Key_0, Key_1, Key_2, Key_3, Key_4, Key_5, Key_6, Key_7, Key_8, Key_9,
	Key_NumPad0, Key_NumPad1, Key_NumPad2, Key_NumPad3, Key_NumPad4, Key_NumPad5, Key_NumPad6, Key_NumPad7, Key_NumPad8, Key_NumPad9,
	Key_NumPad_Period, Key_NumPad_Divide, Key_NumPad_Multiply, Key_NumPad_Minus, Key_NumPad_Plus, Key_NumPad_Enter, Key_NumPad_Equals,
	Key_Colon, Key_Semicolon, Key_Less, Key_Equals, Key_Greater, Key_Question, Key_At, 
	Key_LeftBracket, Key_Backslash, Key_RightBracket, Key_Caret, Key_Underscore, Key_Backquote, 
	Key_A, Key_B, Key_C, Key_D, Key_E, Key_F, Key_G, Key_H, Key_I, Key_J, Key_K, Key_L, Key_M,
	Key_N, Key_O, Key_P, Key_Q, Key_R, Key_S, Key_T, Key_U, Key_V, Key_W, Key_X, Key_Y, Key_Z,
	Key_Delete, Key_Up, Key_Down, Key_Right, Key_Left, Key_Insert, Key_Home, Key_End, Key_PageUp, Key_PageDown,
	Key_F1, Key_F2, Key_F3, Key_F4, Key_F5, Key_F6, Key_F7, Key_F8, Key_F9, Key_F10, Key_F11, Key_F12, Key_F13, Key_F14, Key_F15,
	Key_NumLock, Key_CapsLock, Key_ScrollLock, Key_RightShift, Key_LeftShift, Key_RightControl, Key_LeftControl, Key_RightAlt, Key_LeftAlt,
	Key_Mode, Key_Help, Key_Print, Key_SysReq, Key_Menu, Key_Power,
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
	bool mKeyMemory[_TotalKeys];
	bool mKeyStates[_TotalKeys];
	Vector2d mMousePosition;

	void processEvent(SDL_Event event);
	void processMouseEvent(SDL_Event event);
	void processKeyboardEvent(SDL_Event event);

	void set(int position);
	void clear(int position);
	void toggle(int position);
	bool check(int position);
	bool checkMemory(int position);

	KEY_CODE parse(SDL_Keycode code);
};
extern Input InputManager;