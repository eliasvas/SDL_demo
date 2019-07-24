#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h> 
#include <SDL_mixer.h>
#include <stdio.h>
#include <util.h>
using namespace engine;

namespace engine{
	class Texture{
	public:
		Texture();

		~Texture();

		bool loadFromFile(std::string path);

		bool loadFromRenderedText(std::string textureText, SDL_Color color, TTF_Font* gFont);

		void free();
		
		void render(int x,int y, SDL_Rect *clip = NULL, double angle= 0.0,SDL_Point* center = NULL,SDL_RendererFlip flip = SDL_FLIP_NONE);

		void setColor(uint8_t red, uint8_t green, uint8_t blue);

		void setAlpha(uint8_t alpha);

		int getWidth();
		int getHeight();

	private:
		SDL_Texture* mTexture;

		int mWidth;
		int mHeight;
	};

	void Texture::free(){}

	bool Texture::loadFromRenderedText(std::string textureText, SDL_Color color, TTF_Font* gFont){
		//get rid of preexisting texture
		free();
		
		SDL_Surface* textSurface = TTF_RenderText_Solid(gFont, textureText.c_str(),color);
		if (textSurface == NULL){
			printf("Unable to render text surface!!SDL TTF ERROR: %s\n", TTF_GetError());
		}else {
			mTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
			if (mTexture == NULL){
				printf("unable to create texture from text!!TTF SDL ERROR: %s\n",TTF_GetError());
			}else {
				mWidth = textSurface->w;
				mHeight = textSurface->h;
			}
			SDL_FreeSurface(textSurface);
		}
		return mTexture != NULL;
	}


	void Texture::setAlpha(uint8_t alpha){
		SDL_SetTextureAlphaMod(mTexture, alpha);
	}

	void Texture::setColor(uint8_t red, uint8_t green, uint8_t blue){
		SDL_SetTextureColorMod(mTexture, red,green,blue);
	}

	Texture::Texture(){
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}

	Texture::~Texture(){
		//Deallocate
	}

	bool Texture::loadFromFile(std::string path){
		
		//free
		
		SDL_Texture* newTexture = NULL;
		SDL_Surface* loadedSurface = IMG_Load(path.c_str());
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format,0xff,0xff,0xff));
		if (loadedSurface == NULL){
			printf("Unable to load surface, SDL Error:%s\n", SDL_GetError());
		}else {
			//colorkey
			newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
			if (newTexture == NULL){
				printf("Error creating texture, SDL Error: %s\n", SDL_GetError());
			}else {
				mWidth = loadedSurface->w;
				mHeight = loadedSurface->h;
				//printf("%d|%d|%s\n", mWidth,mHeight,path.c_str());
			}
			SDL_FreeSurface(loadedSurface);
		}
		mTexture = newTexture;
		return mTexture!=NULL;
	}

	int Texture::getWidth() {
		return mWidth;
	}

	int Texture::getHeight() {
		return mHeight;
	}

	void Texture::render(int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip){
		SDL_Rect renderQuad = {x,y,mWidth,mHeight};
		
		if (clip != NULL){
			renderQuad.w = clip->w;
			renderQuad.h = clip->h;
		}

		SDL_RenderCopyEx(gRenderer, mTexture,clip, &renderQuad,angle,center,flip);
	}

}

