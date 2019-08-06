#pragma once
#include <util.h>
#include <ECS.h>
#include <SpriteComponent.h>
#include <CollisionManager.h>

using namespace engine;
namespace engine{
	struct ColliderComponent: public Component{
		SDL_Rect col;
		SpriteComponent* sprite;
		bool drawable = true;
		ColliderComponent(int x, int y, int width, int height){
			col.x = x;
			col.y = y;
			col.w = width;
			col.h = height;
			this->sprite = NULL;
			CollisionManager::add(&col);
		}

		ColliderComponent(SpriteComponent* sprite){
			col.x = 0; 
			col.y = 0;
			col.w = sprite->srcRect.w;
			col.h = sprite->srcRect.h;
			this->sprite = sprite;
			CollisionManager::add(&col);

		}
		bool checkCollision(){
			return CollisionManager::checkCollisionInTable(&col);
		}
		void render(){
			if (sprite == NULL || !drawable)return;
			SDL_Rect renderRect = {sprite->dstRect.x - sprite->camera->x,sprite->dstRect.y - sprite->camera->y, col.w,col.h};
			SDL_RenderDrawRect(gRenderer, &renderRect);
		}
	};
}
