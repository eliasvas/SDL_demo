#pragma once
#include <util.h>
#include <Texture.h>

using namespace engine;

namespace engine{
	struct Entity {
		SDL_Rect srcRect;
		SDL_Rect dstRect;	
		Texture* texture;
		Entity(){}
		Entity(int x, int y, Texture* Texture);
		void render(SDL_Rect& camera);
		void setCamera(SDL_Rect& camera);
	};

	Entity::Entity(int x,int y, Texture* texture){
		dstRect.x = x;
		dstRect.y = y;
		dstRect.w = 32;
		dstRect.h = 32;

		srcRect.x = 0;
		srcRect.y = 0;
		srcRect.w = 32;
		srcRect.h = 32;

		srcRect.x = texture->getWidth();
		srcRect.y = 0;
		srcRect.w = texture->getWidth();
		srcRect.h = texture->getHeight();

		this->texture = texture;
	
	}

	void Entity::render(SDL_Rect& camera){
		dstRect.x -= camera.x;
		dstRect.y -= camera.y;
		texture->render(&srcRect,&dstRect);
		dstRect.x += camera.x;
		dstRect.y += camera.y;	
	}

	void Entity::setCamera( SDL_Rect& camera )
	{
		camera.x = (dstRect.x + texture->getWidth()/2) - SCREEN_WIDTH/2;
		camera.y = (dstRect.y + texture->getHeight()/2) - SCREEN_HEIGHT/2;
		if (camera.x < 0)camera.x = 0;
		if (camera.y < 0)camera.y = 0;
		if (camera.x > LEVEL_WIDTH - camera.w)camera.x = LEVEL_WIDTH - camera.w;
		if (camera.y > LEVEL_HEIGHT - camera.h)camera.y = LEVEL_HEIGHT - camera.h;
	}
}
