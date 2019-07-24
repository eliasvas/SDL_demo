#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h> 
#include <SDL_mixer.h>
#include <stdio.h>
#include <string>
#include <sstream>
#include <vector>
#include <Texture.h>
#include <Timer.h>
#include <Sprite.h>
#include <util.h>
using namespace engine;


SDL_Window *gWindow = NULL;
SDL_Texture *gTexture = NULL;
TTF_Font *gFont = NULL;
Mix_Music *gMusic = NULL;

SDL_Rect playerClips[6];
Texture backgroundTexture;
Texture playerSheetTexture;
Texture gTextTexture;
Texture playerTexture;
Texture tileTexture;


bool init(){
	bool success = true;
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0){
		printf("failed to initialize audio! SDL Error: %s\n", SDL_GetError());
		success = false;
	}

	gWindow = SDL_CreateWindow("Game", SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,SCREEN_WIDTH,SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if(gWindow == NULL){
		printf("Window could not be created!! SDL Error: %s\n", SDL_GetError());
		success = false;
	}else {
		gRenderer  = SDL_CreateRenderer(gWindow,-1,SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);

		if (gRenderer == NULL){
			printf("Renderer could not be created!! SDL Error: %s\n",SDL_GetError());
			success = false;
		}else {
			SDL_SetRenderDrawColor(gRenderer,0,0,0,(uint8_t)0.5);
			int imgFlags = IMG_INIT_PNG;
			if (!(IMG_Init(imgFlags) & imgFlags)){
				printf("SDL_image could not initialize!!SDL Error:%s\n", IMG_GetError());
				success = false;
			}
			if (TTF_Init() == -1){
				printf("SDL ttf could not initialize!!SDL TTF error: %s\n", TTF_GetError());
				success = false;
			}
		}
	}
	if (Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,1,2048) < 0){
		printf("SDL_Mixer could not initialize!!SDL_Mixer Error: %s\n",Mix_GetError());
		success = false;
	}
	return success;
}


SDL_Texture* loadTexture(std::string path) {
	SDL_Texture* newTexture = NULL;

	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL){
		printf("failed to loaf image %s, SDL_Error: %S\n", path.c_str(), SDL_GetError());
	}else {
		newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
		if (newTexture == NULL)
			printf("Unable to create texture, SDL_Error: %s\n", SDL_GetError());
		SDL_FreeSurface(loadedSurface);
	}
	return newTexture;
}



void close() {
	SDL_DestroyTexture(gTexture);
	gTexture = NULL;

	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gRenderer = NULL;
	gWindow = NULL;


	TTF_CloseFont(gFont);
	gFont = NULL;

	Mix_FreeMusic(gMusic);
	gMusic = NULL;

	IMG_Quit();
	TTF_Quit();
	SDL_Quit();
}
bool loadMedia() {
	bool success = true;
	
	playerTexture.loadFromFile("../assets/link.png");

	tileTexture.loadFromFile("../assets/tile.png");

	if (!playerSheetTexture.loadFromFile("../assets/coin2.png")){
		printf("Failed to load texture image!!\n");
		success = false;
	}else {
		
		playerClips[0].x = 52 * 0;
		playerClips[0].y = 0;
		playerClips[0].w = 136;
		playerClips[0].h = 161;
										
						
		playerClips[1].x = 136 * 1;
		playerClips[1].y = 0;
		playerClips[1].w = 136;
		playerClips[1].h = 161;
		
		playerClips[2].x = 136 * 2;
		playerClips[2].y = 0;
		playerClips[2].w = 136;
		playerClips[2].h = 161;
		
		playerClips[3].x = 136 * 3;
		playerClips[3].y = 0;
		playerClips[3].w = 136;
		playerClips[3].h = 161;
		
		playerClips[4].x = 136 * 4;
		playerClips[4].y = 0;
		playerClips[4].w = 136;
		playerClips[4].h = 161;
		
		playerClips[5].x = 136 * 5;
		playerClips[5].y = 0;
		playerClips[5].w = 136;
		playerClips[5].h = 161;
	

	}

	if (!backgroundTexture.loadFromFile("../assets/background.png")){
		printf("Failed to load background texture image!!\n");
		success = false;
	}


	gFont = TTF_OpenFont("../assets/SEASRN__.ttf",40);
	if (gFont != NULL){
		SDL_Color textColor = {0,0,0};
		if (!gTextTexture.loadFromRenderedText("cthulhu fhtagn!", textColor,gFont)){
			printf("failed to render text!!");
			success = false;
		}
	}
	gMusic = Mix_LoadMUS("../assets/loop.wav");
	if (gMusic == NULL){
		printf("couldnt find music..\n");
		success = false;
	}


	return success;
}


int main(int argc, char ** argv){
	init();
	bool quit = false;
	SDL_Event e;
	loadMedia();
	Sprite player(300,200,&playerTexture);
	int scrollingOffset = 0;
	std::vector<Sprite*> tiles(10);
	for (int i = 0; i < 10; ++i){
		tiles[i] = new Sprite((i+10)*32,300,&tileTexture);
	}
	Sprite background(0,0,&backgroundTexture);
	SDL_Rect camera = {0,0,SCREEN_WIDTH,SCREEN_HEIGHT};
	while (!quit){
		while (SDL_PollEvent(&e)!=0){
			if (e.type == SDL_QUIT){
				quit = true;
			}
			player.handleEvent(e);
		}	
		player.move(tiles);
		camera.x = (player.mPosX + player.spriteTexture->getWidth()/2) - SCREEN_WIDTH/2;
		camera.y = (player.mPosY + player.spriteTexture->getHeight()/2) - SCREEN_HEIGHT/2;
		if (camera.x < 0)camera.x = 0;
		if (camera.y < 0)camera.y = 0;
		if (camera.x > LEVEL_WIDTH - camera.w)camera.x = LEVEL_WIDTH - camera.w;
		if (camera.y > LEVEL_HEIGHT - camera.h)camera.y = LEVEL_HEIGHT - camera.h;
		SDL_SetRenderDrawColor(gRenderer,0xff,0xff,0xff,0xff);
		SDL_RenderClear(gRenderer);
		background.render(camera.x,camera.y);
		SDL_SetRenderDrawColor(gRenderer,0,0,0,0xff);
		for (int i = 0; i < 10; ++i){
			tiles[i]->render(camera.x,camera.y);
			//SDL_RenderDrawRect(gRenderer, &tiles[i]->mCollider);
		}
		player.render(camera.x,camera.y);
		SDL_Rect shadow = player.mCollider;
		shadow.x -= camera.x;
		shadow.y -= camera.y;
		SDL_RenderDrawRect(gRenderer,&shadow);
		//tile.render(camera.x,camera.y);
		//printf("[%d,%d]\n",player.mPosX,player.mPosY);
		//printf("[%d,%d]\n",camera.x,camera.y);
		SDL_RenderPresent(gRenderer);
	}
	close();
}
