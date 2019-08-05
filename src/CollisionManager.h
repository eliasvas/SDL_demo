#pragma once
#include <util.h>
using namespace engine;

namespace engine{
	namespace CollisionManager{
		std::vector<SDL_Rect*> colliders;
		void add(SDL_Rect* col){
			colliders.push_back(col);
		}
		bool checkCollisionInTable(SDL_Rect* collider){
			for (int i = 0; i < colliders.size(); i++){
				if (checkCollision(*collider, *colliders[i]) && (colliders[i] != collider))return true;
			}
			return false;
		}
	}
}
