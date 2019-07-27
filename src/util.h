#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h> 
#include <SDL_mixer.h>
#include <stdio.h>
#include <string>
#include <assert.h>
#pragma once

namespace engine{
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



};


