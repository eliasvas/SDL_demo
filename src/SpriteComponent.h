#pragma once
#include <util.h>
#include <ECS.h>

using namespace engine;
namespace engine{
	struct SpriteComponent: public Component{
		SDL_Rect srcRect;
		SDL_Rect dstRect;
		SDL_Rect* camera;
		Texture* texture;


		SpriteComponent(int x,int y,SDL_Rect* lCamera,Texture* lTexture){
			texture = lTexture;
			//printf("%d %d ", lTexture->mWidth,lTexture->mHeight);
			dstRect.x = x;
			dstRect.y = y;
			dstRect.w = 32;
			dstRect.h = 32;

			srcRect.x = 0;
			srcRect.y = 0;
			srcRect.w = 32;
			srcRect.h = 32;


			srcRect.x = 0;
			srcRect.y = 0;
			srcRect.w = 32;//mTexture->getWidth();
			srcRect.h = 32;//mTexture->getHeight();

			camera = lCamera;
		}
		void update(){
			//srcRect.x++;
			
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
