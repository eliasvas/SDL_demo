#pragma once
#include <util.h>

struct PositionComponent: public Component {
	int x;
	int y;
	PositionComponent(int x, int y): x(x),y(x){}
};
