#pragma once
#include <util.h>
#include <AnimatorComponent.h>
#include <SpriteComponent.h>
#include <ColliderComponent.h>

using namespace engine;

namespace engine {
	struct player:public Entity{
		SpriteComponent* sprite;
		AnimatorComponent* animator;
		ColliderComponent* col;
		player(int x,int y,SDL_Rect* camera,Texture* texture, int frames, int differentAnim){
			sprite = &(this->addComponent<SpriteComponent>(x,y,camera,texture));
			animator = &(this->addComponent<AnimatorComponent>(frames,differentAnim,sprite));
			col = &(this->addComponent<ColliderComponent>(sprite));	
			manager.addEntity(this);
		}
	};
}
