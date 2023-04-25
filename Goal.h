#pragma once

#include "Texture.h"

class Goal
{
public:
	Goal(V2d in_pos)
		:
		pos(in_pos)
	{}
public:
	V2d pos;
	V2d dim{ 32.0,32.0 };
	V2i tex_pos{ 0,0 };
	Texture tex{ "Goal", V2i{32,32} };
};