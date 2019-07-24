#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h> 
#include <SDL_mixer.h>
#include <stdio.h>

namespace engine{
	class Timer{
	public:
		Timer();
		void start();
		void stop();
		void pause();
		void unpause();
		uint32_t getTicks();
		bool isStarted();
		bool isPaused();
	private:
		uint32_t mStartTicks;
		uint32_t mPausedTicks;
		bool mPaused;
		bool mStarted;
	};

	Timer::Timer(){
		mStartTicks = 0;
		mPausedTicks = 0;
		mPaused = false;
		mStarted = true;
	}

	void Timer::start(){
		mStarted = true;
		mPaused = false;
		mStartTicks = SDL_GetTicks();
		mPausedTicks = 0;
	}
	void Timer::pause() {
		if (!mPaused && mStarted){
			mPaused = true;
			mPausedTicks = SDL_GetTicks()-mStartTicks;
			mStartTicks = 0;
		}
	}
	void Timer::stop(){
		mStarted = false;
		mPaused = false;
		mStartTicks = 0;
		mPausedTicks = 0;
	}

	void Timer::unpause(){
		if (mStarted && mPaused){
			mPaused = false;
			mStartTicks = SDL_GetTicks() - mPausedTicks;
			mPausedTicks = 0;
		}
	}

	bool Timer::isStarted() {
		return mStarted;
	}

	bool Timer::isPaused() {
		return mPaused;
	}

	uint32_t Timer::getTicks(){
		uint32_t time = 0;
		if (mStarted){
			if (mPaused){
				time = mPausedTicks;
			}
			else {
				time = SDL_GetTicks() - mStartTicks;
			}
		}
		return time;
	}

}
