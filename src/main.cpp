#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h> 
#include <SDL_mixer.h>
#include <stdio.h>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <Texture.h>
#include <Timer.h>
#include <Sprite.h>
#include <util.h>
#include <Tile.h>


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


bool setTiles(Tile *tiles[] = NULL){
	bool tilesLoaded = true;
	int x = 0;
	int y = 0;
	std::ifstream map("../assets/level1.map");
	if (map.fail())
	{
		printf("unable to load map!!\n");
		tilesLoaded = false;
	}else 
	{
		for (int i = 0; i < TOTAL_TILES;++i)
		{
			int tileType = -1;
			map >> tileType;
			//printf("%d\n",tileType);
			if (map.fail())
			{
				printf("error reading file, unexpected EOF\n");
				tilesLoaded = false;
				break;
			}

			if ((tileType >= 0) && (tileType <TOTAL_TILE_SPRITES))
			{
				tiles[i] = new Tile(x,y,tileType);
			}else
			{
				printf("invalid tile type at %d\n",i);
				tilesLoaded = false;
				break;
			}
			x += TILE_WIDTH;
			if (x >=45 * 32) //45 is the width of the level
			{
				x = 0;
				y+=TILE_HEIGHT;
			}	
			
		}	
		if (tilesLoaded)
		{
			tileClips[TILE_TOPLEFT].x = 0;
			tileClips[TILE_TOPLEFT].y = 0;
			tileClips[TILE_TOPLEFT].w = TILE_WIDTH;
			tileClips[TILE_TOPLEFT].h = TILE_HEIGHT;

			tileClips[TILE_TOP].x = 32;
			tileClips[TILE_TOP].y = 0;
			tileClips[TILE_TOP].w = TILE_WIDTH;
			tileClips[TILE_TOP].h = TILE_HEIGHT;

			tileClips[TILE_TOPRIGHT].x = 64;
			tileClips[TILE_TOPRIGHT].y = 0;
			tileClips[TILE_TOPRIGHT].w = TILE_WIDTH;
			tileClips[TILE_TOPRIGHT].h = TILE_HEIGHT;

			tileClips[TILE_LEFT].x = 0;
			tileClips[TILE_LEFT].y = 32;
			tileClips[TILE_LEFT].w = TILE_WIDTH;
			tileClips[TILE_LEFT].h = TILE_HEIGHT;

			tileClips[TILE_CENTER].x = 32;
			tileClips[TILE_CENTER].y = 32;
			tileClips[TILE_CENTER].w = TILE_WIDTH;
			tileClips[TILE_CENTER].h = TILE_HEIGHT;

			tileClips[TILE_RIGHT].x = 64;
			tileClips[TILE_RIGHT].y = 32;
			tileClips[TILE_RIGHT].w = TILE_WIDTH;
			tileClips[TILE_RIGHT].h = TILE_HEIGHT;

			tileClips[TILE_BOTTOMLEFT].x = 0;
			tileClips[TILE_BOTTOMLEFT].y = 64;
			tileClips[TILE_BOTTOMLEFT].w = TILE_WIDTH;
			tileClips[TILE_BOTTOMLEFT].h = TILE_HEIGHT;
	
			tileClips[TILE_BOTTOM].x = 32;
			tileClips[TILE_BOTTOM].y = 64;
			tileClips[TILE_BOTTOM].w = TILE_WIDTH;
			tileClips[TILE_BOTTOM].h = TILE_HEIGHT;

			tileClips[TILE_BOTTOMRIGHT].x = 64;
			tileClips[TILE_BOTTOMRIGHT].y = 64;
			tileClips[TILE_BOTTOMRIGHT].w = TILE_WIDTH;
			tileClips[TILE_BOTTOMRIGHT].h = TILE_HEIGHT;



		}
	}
	map.close();

	return tilesLoaded;
}


bool loadMedia(Tile* tiles[] = NULL) {
	bool success = true;
	
	playerTexture.loadFromFile("../assets/link-spritesheet.png");

	tileTexture.loadFromFile("../assets/tile.png");

	tilesetTexture.loadFromFile("../assets/tileset.png");

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

	if (!setTiles(tiles)){
		printf("failed to load tiles");
		success = false;
	}

	return success;
}

int main(int argc, char ** argv){
	init();
	bool quit = false;
	SDL_Event e;
	
	Tile* tileSet[TOTAL_TILES];
	if(!loadMedia(tileSet))printf("couldnt load tileset!");
	Sprite player(300,300,&playerTexture, 2, 100);
	int scrollingOffset = 0;
	Sprite background(0,0,&backgroundTexture);
	SDL_Rect camera = {0,0,SCREEN_WIDTH,SCREEN_HEIGHT};
	while (!quit){
		while (SDL_PollEvent(&e)!=0){
			if (e.type == SDL_QUIT){
				quit = true;
			}
			player.handleEvent(e);
		}	
		player.move(tileSet);
		player.setCamera(camera);
		SDL_SetRenderDrawColor(gRenderer,0xff,0xff,0xff,0xff);
		SDL_RenderClear(gRenderer);
		//background.render(camera.x,camera.y);
		SDL_SetRenderDrawColor(gRenderer,0,0,0,0xff);
		for (int i = 0; i < TOTAL_TILES; ++i){
			tileSet[i]->render(camera);
		}
		player.render(camera);
		SDL_Rect shadow = player.mCollider;
		shadow.x -= camera.x;
		shadow.y -= camera.y;
		SDL_RenderDrawRect(gRenderer,&shadow);
		SDL_RenderPresent(gRenderer);
	}
	close();
}
