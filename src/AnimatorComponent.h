#include <util.h>
struct AnimatorComponent{
	bool animated = false;
	int frameDelay = 100;
	int frames = 0;
	int numberOfAnimations = 0;
	int currentNumOfAnimation = 0;
	int currentFrame = 0; //NOTE:  noone change this, if put to 0 restarts current anim
	
	
};
