#pragma once
#include <util.h>
#include <ECS.h>
#include <PositionComponent.h>

using namespace engine;
namespace engine{
	struct SpriteComponent: public Component{
		SDL_Rect srcRect;
		SDL_Rect dstRect;
		SDL_Rect* camera;
		Texture* texture;
		PositionComponent* pos;


		SpriteComponent(int x,int y,SDL_Rect* lCamera,Texture* lTexture){
			texture = lTexture;
			pos = new PositionComponent(x,y);
			dstRect.x = 0;
			dstRect.y = 0;
			dstRect.w = 32;
			dstRect.h = 32;

			srcRect.x = 0;
			srcRect.y = 0;
			srcRect.w = 32;
			srcRect.h = 32;


			srcRect.x = 0;
			srcRect.y = 0;
			srcRect.w = lTexture->getWidth();
			srcRect.h = lTexture->getHeight();

			camera = lCamera;
		}
		SpriteComponent(int x,int y,SDL_Rect* lCamera,Texture* lTexture, SDL_Rect* clip){
			texture = lTexture;
			pos = new PositionComponent(x,y);
			dstRect.x = 0;
			dstRect.y = 0;
			dstRect.w = 32;
			dstRect.h = 32;

			srcRect.x = clip->x;
			srcRect.y = clip->y;
			srcRect.w = clip->w;
			srcRect.h = clip->h;


			srcRect.x = 0;
			srcRect.y = 0;
			srcRect.w = clip->w;
			srcRect.h = clip->h;

			camera = lCamera;
		}

		void update(){
			//srcRect.x++;
			pos->update();
			dstRect.x = pos->x;
			dstRect.y = pos->y;
		}
		void renderr(SDL_Rect camera){
			dstRect.x -= camera.x;
			dstRect.y -= camera.y;
			texture->render(&srcRect,&dstRect);
			dstRect.x += camera.x;
			dstRect.y += camera.y;
		}

		void render(){
			dstRect.x -= camera->x;
			dstRect.y -= camera->y;
			texture->render(&srcRect,&dstRect);
			dstRect.x += camera->x;
			dstRect.y += camera->y;
		}
	};

}
