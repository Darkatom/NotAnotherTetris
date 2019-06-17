#pragma once
#include <SDL.h>

// Source: http://lazyfoo.net/tutorials/SDL/23_advanced_timers/index.php
class Timer {
public:
	Timer();
	~Timer();

	void start();
	void stop();
	void pause();
	void resume();

	Uint32 getTicks();
	bool isStarted();
	bool isPaused();

private:
	bool mStarted;
	bool mPaused;
	Uint32 mStartTicks;
	Uint32 mPausedTicks;
};
