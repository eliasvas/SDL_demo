#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h> 
#include <SDL_mixer.h>
#include <stdio.h>
#include <string>
#include <util.h>
#include <Texture.h>

using namespace engine;

Texture tilesetTexture;
SDL_Rect tileClips[TOTAL_TILE_SPRITES];
namespace engine{
	struct Tile{
		static const int TILE_W = 32;
		static const int TILE_H = 32;
		Tile(int x,int y,Texture* texture);
		Tile(int x,int y,int type);
		Tile();
		void handleEvent(SDL_Event& e);
		//void move();
		void move(std::vector<Tile*> tiles);
		void render(SDL_Rect& camera);


		int mPosX, mPosY;
		SDL_Rect mCollider;
		int mType;
	};


	Tile::Tile(int x,int y,Texture* texture){
		mPosX = x;
		mPosY = y;

		mCollider.x = mPosX;
		mCollider.y = mPosY;
		mCollider.w = texture->getWidth();
		mCollider.h = texture->getHeight();

	}

	Tile::Tile(int x,int y,int type){
		mPosX = x;
		mPosY = y;

		mCollider.x = mPosX;
		mCollider.y = mPosY;
		mCollider.w = TILE_WIDTH;
		mCollider.h = TILE_HEIGHT;

		
		mType = type;
	}


	Tile::Tile(){}


	void Tile::render(SDL_Rect& camera){
		if (checkCollision(camera,mCollider))
			tilesetTexture.render(mPosX-camera.x,mPosY-camera.y, &tileClips[mType]);	
	}



}

