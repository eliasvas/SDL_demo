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
		if (tiles[i]->solid){
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
		Sprite(int x,int y,Texture* texture, int frames, int frameDelay);
		Sprite(int x,int y,Texture* texture, int frames,int numOfAnimations, int frameDelay);
		Sprite();
		Sprite(int x,int y,Texture* texture,SDL_Rect& col);
		void handleEvent(SDL_Event& e);
		void move(std::vector<Sprite*> tiles);
		void move(std::vector<SDL_Rect*> col);
		void move(Tile* tiles[]);
		void setCamera(SDL_Rect& camera);
		void render(SDL_Rect& camera);
		void animate();
		void physicallyAnimate(int delayModifier = 16);
		void changeToAnimationNum(int num);
		void changeToFrame(int frame);


		SDL_Rect srcRect, dstRect;
		int mVelX, mVelY;
		Texture* spriteTexture;
		SDL_Rect mCollider;


		//animatior component
		bool animated = false;
		int frameDelay = 100;
		int frames = 0;
		int numberOfAnimations = 0;
		int currentNumOfAnimation = 0;
		int currentFrame = 0;
	};


	Sprite::Sprite(int x,int y,Texture* texture){
		dstRect.x = x;
		dstRect.y = y;
		dstRect.w = 32;
		dstRect.h = 32;

		srcRect.x = 0;
		srcRect.y = 0;
		srcRect.w = 32;
		srcRect.h = 32;

		mVelX = 0;
		mVelY = 0;

		srcRect.x = texture->getWidth();
		srcRect.y = 0;
		srcRect.w = texture->getWidth();
		srcRect.h = texture->getHeight();


		mCollider.x = dstRect.x;
		mCollider.y = dstRect.y;
		mCollider.w = texture->getWidth();
		mCollider.h = texture->getHeight();

		spriteTexture = texture;
	}
	Sprite::Sprite(int x,int y,Texture* texture, int frames,int numOfAnimations, int frameDelay){
		assert(numOfAnimations > 0);
		dstRect.x = x;
		dstRect.y = y;
		dstRect.w = 32;
		dstRect.h = 32;


		srcRect.x = texture->getWidth() / frames;
		srcRect.y = 0;
		srcRect.w = texture->getWidth() / frames;
		srcRect.h = texture->getHeight() / numOfAnimations; //@Check

		mVelX = 0;
		mVelY = 0;

		mCollider.x = dstRect.x;
		mCollider.y = dstRect.y;
		mCollider.w = texture->getWidth() / frames;
		mCollider.h = texture->getHeight() / numOfAnimations;

		spriteTexture = texture;

		animated = true;
		this->frameDelay = frameDelay;
		this->frames = frames;
		numberOfAnimations = numOfAnimations;

	}

	Sprite::Sprite(int x,int y,Texture* texture, int frames, int frameDelay){
		dstRect.x = x;
		dstRect.y = y;
		dstRect.w = 32;
		dstRect.h = 32;


		srcRect.x = texture->getWidth() / frames;
		srcRect.y = 0;
		srcRect.w = texture->getWidth() / frames;
		srcRect.h = texture->getHeight();

		mVelX = 0;
		mVelY = 0;

		mCollider.x = dstRect.x;
		mCollider.y = dstRect.y;
		mCollider.w = texture->getWidth() / frames;
		mCollider.h = texture->getHeight();

		spriteTexture = texture;

		animated = true;
		this->frameDelay = frameDelay;
		this->frames = frames;
	}

	Sprite::Sprite(int x,int y,Texture* texture, SDL_Rect& col){
		dstRect.x = x;
		dstRect.y = y;
		dstRect.w = 32;
		dstRect.h = 32;

		srcRect.x = texture->getWidth();
		srcRect.y = 0;
		srcRect.w = texture->getWidth();
		srcRect.h = texture->getHeight();


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
				case SDLK_e: changeToAnimationNum(1);break;
				case SDLK_q: changeToFrame(1);break;
			}
		}else if (e.type == SDL_KEYUP && e.key.repeat == 0){
			switch(e.key.keysym.sym){
				case SDLK_UP: mVelY += SPRITE_VEL;break;
				case SDLK_DOWN: mVelY -= SPRITE_VEL;break;
				case SDLK_LEFT: mVelX += SPRITE_VEL;break;
				case SDLK_RIGHT: mVelX -= SPRITE_VEL;break;
				case SDLK_e: changeToAnimationNum(0);break;
			}
		}
	}

	bool checkCollision (SDL_Rect& mCollider,std::vector<SDL_Rect*> col){
		for (int i = 0; i < col.size(); ++i){
			if (checkCollision(mCollider, *col[i]))return true;
		}
		return false;
	}

	bool checkCollision (SDL_Rect& mCollider,std::vector<Sprite*> tiles){
		for (int i = 0; i < tiles.size(); ++i){
			if (checkCollision(mCollider, tiles[i]->mCollider))return true;
		}
		return false;
	}

	void Sprite::move(std::vector<SDL_Rect*> col){
		dstRect.x += mVelX;
		mCollider.x = dstRect.x;
		if((dstRect.x < 0)||(dstRect.x + spriteTexture->getWidth()> LEVEL_WIDTH)|| (checkCollision(mCollider,col))){
			dstRect.x -= mVelX;
			mCollider.x = dstRect.x;
		}
		dstRect.y += mVelY;
		mCollider.y = dstRect.y;
		if((dstRect.y < 0)||(dstRect.y + spriteTexture->getHeight()> LEVEL_HEIGHT)||(checkCollision(mCollider,col))){
			dstRect.y -= mVelY;
			mCollider.y = dstRect.y;
		}

	}

	void Sprite::move(std::vector<Sprite*> tiles){
		dstRect.x += mVelX;
		mCollider.x = dstRect.x;
		if((dstRect.x < 0)||(dstRect.x + spriteTexture->getWidth()> LEVEL_WIDTH)|| (checkCollision(mCollider,tiles))){
			dstRect.x -= mVelX;
			mCollider.x = dstRect.x;
		}
		dstRect.y += mVelY;
		mCollider.y = dstRect.y;
		if((dstRect.y < 0)||(dstRect.y + spriteTexture->getHeight()> LEVEL_HEIGHT)||(checkCollision(mCollider,tiles))){
			dstRect.y -= mVelY;
			mCollider.y = dstRect.y;
		}

	}


	void Sprite::move(Tile* tiles[]){
		physicallyAnimate();
		dstRect.x += mVelX;
		mCollider.x = dstRect.x;
		if((dstRect.x < 0)||(dstRect.x + spriteTexture->getWidth()> LEVEL_WIDTH)|| (touchesWall(mCollider,tiles))){
			dstRect.x -= mVelX;
			mCollider.x = dstRect.x;
		}
		dstRect.y += mVelY;
		mCollider.y = dstRect.y;
		if((dstRect.y < 0)||(dstRect.y + spriteTexture->getHeight()> LEVEL_HEIGHT)||(touchesWall(mCollider,tiles))){
			dstRect.y -= mVelY;
			mCollider.y = dstRect.y;
		}

	}


	void Sprite::render(SDL_Rect& camera){
		dstRect.x -= camera.x;
		dstRect.y -= camera.y;
		spriteTexture->render(&srcRect,&dstRect);
		dstRect.x += camera.x;
		dstRect.y += camera.y;	
	}

	void Sprite::setCamera( SDL_Rect& camera )
	{
		camera.x = (dstRect.x + spriteTexture->getWidth()/2) - SCREEN_WIDTH/2;
		camera.y = (dstRect.y + spriteTexture->getHeight()/2) - SCREEN_HEIGHT/2;
		if (camera.x < 0)camera.x = 0;
		if (camera.y < 0)camera.y = 0;
		if (camera.x > LEVEL_WIDTH - camera.w)camera.x = LEVEL_WIDTH - camera.w;
		if (camera.y > LEVEL_HEIGHT - camera.h)camera.y = LEVEL_HEIGHT - camera.h;
	}

	//@WARNING: This type of animation displays fixed frames per milisecond (%)
	//this works if we want our animations to continue to their previous framecounts when changing!!!
	void Sprite::animate(){
		if (animated){
			srcRect.x = srcRect.w * ((int)(SDL_GetTicks()/frameDelay) % frames);
		}
	}

	void Sprite::physicallyAnimate(int delayModifier){
		if (!animated)return;
		assert(delayModifier > 0);
		++currentFrame;
		if (currentFrame/frames >= (frames*delayModifier))currentFrame=0;
		changeToFrame(currentFrame/(frames*delayModifier));		
	}

	void Sprite::changeToAnimationNum(int num){
		currentFrame = 0; //restarting animations
		if (num > numberOfAnimations-1)num = 0; //TODO cancel current
		if (num == currentNumOfAnimation || numberOfAnimations == 0)return;
		srcRect.y = (srcRect.h)* num;
		currentNumOfAnimation = num;
	}
	void Sprite::changeToFrame(int frame){
		if (frames == 0)return;
		if (frame > frames-1)frame = 0; //TODO cancel current
		srcRect.x = (srcRect.w)* frame;
	}
}

