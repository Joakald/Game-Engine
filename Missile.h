#pragma once
#include "BaseGeometry.h"
#include "Sound.h"
#include "Texture.h"
#include "Wall.h"

class Missile
{
public:
	enum State
	{
		active,
		exploding,
		inactive
	};
public:
	void Activate(V2d player_pos, V2d mouse_pos)
	{
		state = active;
		pos = player_pos + V2d{ 16.0,16.0 };
		dir = ((mouse_pos - pos) * speed) 
			/ pos.GetDistance(mouse_pos);
		shoot.Play();
	}
	void Explode(double& dt)
	{
		if (timer == 0.0)
			explode.Play();
		timer += dt;
		if (timer < 0.25)
			tex_pos = V2i{ 8,0 };
		if (timer > 0.25 && timer <= 0.5)
			tex_pos = V2i{ 16,0 };
		if (timer > 0.5 && timer <= 0.75)
			tex_pos = V2i{ 24,0 };
		if (timer > 0.75)
		{
			tex_pos = V2i{ 0,0 };
			state = State::inactive;
			pos = V2d{ 0.0, 0.0 };
			dir = V2d{ 0.0, 0.0 };
			timer = 0.0;
		}
	}
	void ScreenCollision()
	{
		if (pos.x < 0.0)
		{
			state = exploding;
		}
		if (pos.x + dim.x > 799.0)
		{
			state = exploding;
		}
		if (pos.y < 0.0)
		{
			state = exploding;
		}
		if (pos.y + dim.y > 599.0)
		{
			state = exploding;
		}
	}
	void WallCollision(Wall& w)
	{
		// left
		if (pos.x < w.pos.x && pos.x + dim.x > w.pos.x)
		{
			// top left
			if (pos.y < w.pos.y && pos.y + dim.y > w.pos.y)
			{
				state = exploding;
			}
			// mid left
			if (pos.y > w.pos.y && pos.y + dim.y < w.pos.y + w.dim.y)
			{
				state = exploding;
			}
			// bottom left
			if (pos.y < w.pos.y + w.dim.y && pos.y + dim.y > w.pos.y + w.dim.y)
			{
				state = exploding;
			}
		}
		// right
		else if (pos.x < w.pos.x + w.dim.x && pos.x + dim.x > w.pos.x + w.dim.x)
		{
			// top right
			if (pos.y < w.pos.y && pos.y + dim.y > w.pos.y)
			{
				state = exploding;
			}
			// mid right
			if (pos.y > w.pos.y && pos.y + dim.y < w.pos.y + w.dim.y)
			{
				state = exploding;
			}
			// bottom right
			if (pos.y < w.pos.y + w.dim.y && pos.y + dim.y > w.pos.y + w.dim.y)
			{
				state = exploding;
			}
		}
		// mid
		if (pos.x > w.pos.x && pos.x + dim.x < w.pos.x + w.dim.x)
		{
			// up mid
			if (pos.y < w.pos.y && pos.y + dim.y > w.pos.y)
				state = exploding;
			// down mid
			if (pos.y < w.pos.y + w.dim.y && pos.y + dim.y > w.pos.y + w.dim.y)
				state = exploding;
		}
	}
public:
	State state = State::inactive;
	double speed = 400.0;
	V2d dir{ 0.0,0.0 };
	V2d pos{ 0.0,0.0 };
	V2d dim{ 8.0,8.0 };
	V2i tex_pos{ 0,0 };
	Sound shoot{ "Tsh" };
	Sound explode{ "Poff" };
	Texture tex{ "Missile", V2i{8,8} };
	double timer = 0.0;
};