#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h> 
#include <SDL_mixer.h>
#include <stdio.h>
#include <string>
#include <util.h>
#include <Tile.h>

using namespace engine;

bool touchesWall(SDL_Rect box, Tile* tiles[]){
	for (int i = 0; i < TOTAL_TILES;++i){
		if (tiles[i]->mType == 0 || tiles[i]->mType == 1){
			if (checkCollision(box, tiles[i]->mCollider)){
				return true;
			}
		}
	}
	return false;
}

namespace engine{
	struct Sprite{
	public:
		static const int SPRITE_VEL = 5;
		Sprite(int x,int y,Texture* texture);
		Sprite();
		Sprite(int x,int y,Texture* texture,SDL_Rect& col);
		void handleEvent(SDL_Event& e);
		//void move();
		void move(std::vector<Sprite*> tiles);
		void move(Tile* tiles[]);
		void setCamera(SDL_Rect& camera);
		void render(int camX,int camY);


		int mPosX, mPosY;
		int mVelX, mVelY;
		Texture* spriteTexture;
		SDL_Rect mCollider;
	};


	Sprite::Sprite(int x,int y,Texture* texture){
		mPosX = x;
		mPosY = y;

		mVelX = 0;
		mVelY = 0;

		mCollider.x = mPosX;
		mCollider.y = mPosY;
		mCollider.w = texture->getWidth();
		mCollider.h = texture->getHeight();

		spriteTexture = texture;
	}

	Sprite::Sprite(int x,int y,Texture* texture, SDL_Rect& col){
		mPosX = x;
		mPosY = y;

		mVelX = 0;
		mVelY = 0;

		mCollider.x = col.x;
		mCollider.y = col.y;
		mCollider.w = col.w;
		mCollider.h = col.h;


		spriteTexture = texture;
	}

	Sprite::Sprite(){}


	void Sprite::handleEvent(SDL_Event& e){
		if (e.type == SDL_KEYDOWN && e.key.repeat == 0){
			switch(e.key.keysym.sym){
				case SDLK_UP: mVelY -= SPRITE_VEL;break;
				case SDLK_DOWN: mVelY += SPRITE_VEL;break;
				case SDLK_LEFT: mVelX -= SPRITE_VEL;break;
				case SDLK_RIGHT: mVelX += SPRITE_VEL;break;
			}
		}else if (e.type == SDL_KEYUP && e.key.repeat == 0){
			switch(e.key.keysym.sym){
				case SDLK_UP: mVelY += SPRITE_VEL;break;
				case SDLK_DOWN: mVelY -= SPRITE_VEL;break;
				case SDLK_LEFT: mVelX += SPRITE_VEL;break;
				case SDLK_RIGHT: mVelX -= SPRITE_VEL;break;
			}
		}
	}

	bool checkCollision (SDL_Rect& mCollider,std::vector<Sprite*> tiles){
		for (int i = 0; i < tiles.size(); ++i){
			if (checkCollision(mCollider, tiles[i]->mCollider))return true;
		}
		return false;
	}

	void Sprite::move(std::vector<Sprite*> tiles){
		mPosX += mVelX;
		mCollider.x = mPosX;
		if((mPosX < 0)||(mPosX + spriteTexture->getWidth()> LEVEL_WIDTH)|| (checkCollision(mCollider,tiles))){
			mPosX -= mVelX;
			mCollider.x = mPosX;
		}
		mPosY += mVelY;
		mCollider.y = mPosY;
		if((mPosY < 0)||(mPosY + spriteTexture->getHeight()> LEVEL_HEIGHT)||(checkCollision(mCollider,tiles))){
			mPosY -= mVelY;
			mCollider.y = mPosY;
		}

	}


	void Sprite::move(Tile* tiles[]){
		mPosX += mVelX;
		mCollider.x = mPosX;
		if((mPosX < 0)||(mPosX + spriteTexture->getWidth()> LEVEL_WIDTH)|| (touchesWall(mCollider,tiles))){
			mPosX -= mVelX;
			mCollider.x = mPosX;
		}
		mPosY += mVelY;
		mCollider.y = mPosY;
		if((mPosY < 0)||(mPosY + spriteTexture->getHeight()> LEVEL_HEIGHT)||(touchesWall(mCollider,tiles))){
			mPosY -= mVelY;
			mCollider.y = mPosY;
		}

	}


	void Sprite::render(int camX,int camY){
		spriteTexture->render(mPosX-camX,mPosY-camY);	
	}

	void Sprite::setCamera( SDL_Rect& camera )
	{
		camera.x = (mPosX + spriteTexture->getWidth()/2) - SCREEN_WIDTH/2;
		camera.y = (mPosY + spriteTexture->getHeight()/2) - SCREEN_HEIGHT/2;
		if (camera.x < 0)camera.x = 0;
		if (camera.y < 0)camera.y = 0;
		if (camera.x > LEVEL_WIDTH - camera.w)camera.x = LEVEL_WIDTH - camera.w;
		if (camera.y > LEVEL_HEIGHT - camera.h)camera.y = LEVEL_HEIGHT - camera.h;
	}

}

