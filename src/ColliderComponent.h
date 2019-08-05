#pragma once
#include <ECS.h>
#include <SpriteComponent.h>
#include <CollisionManager.h>

using namespace engine;
namespace engine{
	struct ColliderComponent: public Component{
		SDL_Rect col;
		ColliderComponent(int x, int y, int width, int height){
			col.x = x;
			col.y = y;
			col.w = width;
			col.h = height;
			CollisionManager::add(&col);
		}

		ColliderComponent(SpriteComponent* sprite){
			col.x = 0; 
			col.y = 0;
			col.w = sprite->srcRect.w;
			col.h = sprite->srcRect.h;
			CollisionManager::add(&col);

		}
		bool checkCollision(){
			return CollisionManager::checkCollisionInTable(&col);
		}
	};
}
