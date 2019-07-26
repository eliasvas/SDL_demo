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
		Sprite(int x,int y,Texture* texture, int frames, int frameDelay);
		Sprite();
		Sprite(int x,int y,Texture* texture,SDL_Rect& col);
		void handleEvent(SDL_Event& e);
		//void move();
		void move(std::vector<Sprite*> tiles);
		void move(Tile* tiles[]);
		void setCamera(SDL_Rect& camera);
		void render(SDL_Rect& camera);
		void animate();


		SDL_Rect srcRect, dstRect;
		int mVelX, mVelY;
		Texture* spriteTexture;
		SDL_Rect mCollider;
		bool animated = false;
		int frameDelay = 100;
		int frames = 0;
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

		mCollider.x = dstRect.x;
		mCollider.y = dstRect.y;
		mCollider.w = texture->getWidth();
		mCollider.h = texture->getHeight();

		spriteTexture = texture;
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
		animate();
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

	void Sprite::animate(){
		if (animated){
			srcRect.x = srcRect.w * ((int)(SDL_GetTicks()/frameDelay) % frames);
		}
	}

}

