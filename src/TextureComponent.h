#pragma once
#include <util.h>
#include <ECS.h>

struct TextureComponent: public Component {
	SDL_Texture* texture;

};
