#pragma once

#include "BaseGeometry.h"

class Wall
{
public:
	Wall(V2d in_pos, V2d in_dim, Color in_color)
		:
		pos(in_pos),
		dim(in_dim),
		c(in_color)
	{}
public:
	// position	
	V2d pos;
	V2d dim;
	// image
	Color c;
};
