#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h> 
#include <SDL_mixer.h>
#include <stdio.h>
#include <string>
#include <util.h>

using namespace engine;

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
		void render(int camX,int camY);


		int mPosX, mPosY;
		int mVelX, mVelY;
		Texture* spriteTexture;
		SDL_Rect mCollider;
	};


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


	void Sprite::render(int camX,int camY){
		spriteTexture->render(mPosX-camX,mPosY-camY);	
	}


}

