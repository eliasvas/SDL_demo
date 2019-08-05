#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h> 
#include <SDL_mixer.h>
#include <stdio.h>
#include <string>
#include <assert.h>
#include <ECS.h>


namespace engine{
	
	EntityManager manager;
	uint32_t componentCount = 0;
	const int FPS = 60;
	int frameDelay = 1000/FPS; //max time between frames meaning 1 second per FPS=60
	uint32_t frameStart;
	int frameTime;
	

	const int SCREEN_WIDTH = 800;
	const int SCREEN_HEIGHT = 600;

	const int LEVEL_WIDTH = 1440;
	const int LEVEL_HEIGHT = 670;
	SDL_Renderer* gRenderer = NULL;
	const int TOTAL_TILES = 21 * 45;
	const int TOTAL_TILE_SPRITES = 9;
	const int TILE_WIDTH = 32;
	const int TILE_HEIGHT = 32;

	//The different tile sprites
	const int TILE_CENTER = 4;
	const int TILE_TOP = 1;
	const int TILE_TOPRIGHT = 2;
	const int TILE_RIGHT = 5;
	const int TILE_BOTTOMRIGHT = 8;
	const int TILE_BOTTOM = 7;
	const int TILE_BOTTOMLEFT = 6;
	const int TILE_LEFT = 3;
	const int TILE_TOPLEFT = 0;


	bool checkCollision(SDL_Rect& a, SDL_Rect& b){
		int leftA,leftB;
		int rightA, rightB;
		int topA, topB;
		int bottomA, bottomB;

		leftA = a.x;
		rightA = a.x + a.w;
		topA = a.y;
		bottomA = a.y + a.h;

		leftB = b.x;
		rightB = b.x + b.w;
		topB = b.y;
		bottomB = b.y + b.h;

		if (bottomA <= topB)return false;
		if (topA >= bottomB)return false;
		if (rightA <= leftB)return false;
		if (leftA >= rightB)return false;
		//printf("collision in [%d, %d] and [%d, %d]\n", a.x,a.y,b.x,b.y);
		return true;
	}

		void setCamera(SDL_Rect* camera, SDL_Rect* dstRect)
		{
			camera->x = (dstRect->x + 16) - SCREEN_WIDTH/2;
			camera->y = (dstRect->y + 16) - SCREEN_HEIGHT/2;
			if (camera->x < 0)camera->x = 0;
			if (camera->y < 0)camera->y = 0;
			if (camera->x > LEVEL_WIDTH - camera->w)camera->x = LEVEL_WIDTH - camera->w;
			if (camera->y > LEVEL_HEIGHT - camera->h)camera->y = LEVEL_HEIGHT - camera->h;
		}


};


