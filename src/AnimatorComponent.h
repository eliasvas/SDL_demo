#pragma once
#include <util.h>
#include <ECS.h>
#include <SpriteComponent.h>
struct AnimatorComponent : public Component{
	bool animated = false;
	int frameDelay = 100;
	int frames = 0;
	int numberOfAnimations = 0;
	int currentNumOfAnimation = 0;
	int currentFrame = 0; //NOTE:  noone change this, if put to 0 restarts current anim
	SpriteComponent* sprite;


	AnimatorComponent(int frames, int numberOfAnimations,Entity* e) {
		entity = e;
		if (!entity->hasComponent<SpriteComponent>())
			sprite = (SpriteComponent*)entity->getComponent<SpriteComponent>();
	}

	void animate(){
		if (animated){
			sprite->srcRect.x = sprite->srcRect.w * ((int)(SDL_GetTicks()/frameDelay) % frames);
		}
	}

	void physicallyAnimate(int delayModifier){
		if (!animated)return;
		//assert(delayModifier > 0);
		++currentFrame;
		if (currentFrame/frames >= (frames*delayModifier))currentFrame=0;
		changeToFrame(currentFrame/(frames*delayModifier));		
	}

	void changeToAnimationNum(int num){
		currentFrame = 0; //restarting animations
		if (num > numberOfAnimations-1)num = 0; //TODO cancel current
		if (num == currentNumOfAnimation || numberOfAnimations == 0)return;
		sprite->srcRect.y = (sprite->srcRect.h)* num;
		currentNumOfAnimation = num;
	}
	void changeToFrame(int frame){
		if (frames == 0)return;
		if (frame > frames-1)frame = 0; //TODO cancel current
		sprite->srcRect.x = (sprite->srcRect.w)* frame;
	}

};
