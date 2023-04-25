#pragma once

#include "Texture.h"
#include "Sound.h"
#include "Missile.h"

class Olof
{
public:
	enum State
	{
		alive,
		dying,
		dead
	};
public:
	Olof(std::string texture_name, V2i in_pic_dim, std::string in_dying_sound, V2d in_pos, V2d in_dir, State in_state)
		:
		pos(in_pos),
		dir(in_dir),
		tex(texture_name, in_pic_dim),
		dying_sound(dying_sound),
		state(in_state)
	{
		dim.x = (double)in_pic_dim.x;
		dim.y = (double)in_pic_dim.y;
	}
	void ScreenCollision()
	{
		if (pos.x < 0.0)
		{
			pos.x = 0.0;
			dir.x *= -1.0;
		}
		if (pos.x + dim.x > 799.0)
		{
			pos.x = 799.0 - dim.x;
			dir.x *= -1.0;
		}
		if (pos.y < 0.0)
		{
			pos.y = 0.0;
			dir.y *= -1.0;
		}
		if (pos.y + dim.y > 599.0)
		{
			pos.y = 599.0 - dim.y;
			dir.y *= -1.0;
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
				double x_diff = pos.x + dim.x - w.pos.x;
				double y_diff = pos.y + dim.y - w.pos.y;
				if (x_diff >= y_diff)
				{
					dir.y *= -1.0;
					pos.y = w.pos.y - dim.y;
				}
				else
				{
					dir.x *= -1.0;
					pos.x = w.pos.x - dim.x;
				}
			}
			// mid left
			else if (pos.y > w.pos.y && pos.y + dim.y < w.pos.y + w.dim.y)
			{
				pos.x = w.pos.x - dim.x;
				dir.x *= -1.0;
			}
			// bottom left
			else if (pos.y < w.pos.y + w.dim.y && pos.y + dim.y > w.pos.y + w.dim.y)
			{
				double x_diff = pos.x + dim.x - w.pos.x;
				double y_diff = w.pos.y + w.dim.y - pos.y;
				if (x_diff >= y_diff)
				{
					dir.y *= -1.0;
					pos.y = w.pos.y + w.dim.y;
				}
				else
				{
					dir.x *= -1.0;
					pos.x = w.pos.y - dim.x;
				}
			}
			// caller engulfs
			else if (pos.y < w.pos.y && pos.y + dim.y > w.pos.y + w.dim.y)
			{
				dir.x *= -1.0;
				pos.x = w.pos.x - dim.x;
			}
		}
		// right
		else if (pos.x < w.pos.x + w.dim.x && pos.x + dim.x > w.pos.x + w.dim.x)
		{
			// top right
			if (pos.y < w.pos.y && pos.y + dim.y > w.pos.y)
			{
				double x_diff = w.pos.x + w.dim.x - pos.x;
				double y_diff = pos.y + dim.y - w.pos.y;
				if (x_diff >= y_diff)
				{
					dir.y *= -1.0;
					pos.y = w.pos.y - dim.y;
				}
				else
				{
					dir.x *= -1.0;
					pos.x = w.pos.x + w.dim.x;
				}
			}
			// mid right
			else if (pos.y > w.pos.y && pos.y + dim.y < w.pos.y + w.dim.y)
			{
				dir.x *= -1.0;
				pos.x = w.pos.x + w.dim.x;
			}
			// bottom right
			else if (pos.y < w.pos.y + w.dim.y && pos.y + dim.y > w.pos.y + w.dim.y)
			{
				double x_diff = w.pos.x + w.dim.x - pos.x;
				double y_diff = w.pos.y + w.dim.y - pos.y;
				if (x_diff >= y_diff)
				{
					dir.y *= -1.0;
					pos.y = w.pos.y + w.dim.y;
				}
				else
				{
					dir.x *= -1.0;
					pos.x = w.pos.x + w.dim.x;
				}
			}
			// caller engulfs
			else if (pos.y < w.pos.y && pos.y + dim.y > w.pos.y + w.dim.y)
			{
				dir.x *= -1.0;
				pos.x = w.pos.x + w.dim.x;
			}
		}
		// mid, argument engulfs
		if (pos.x > w.pos.x && pos.x + dim.x < w.pos.x + w.dim.x)
		{
			// top mid
			if (pos.y < w.pos.y && pos.y + dim.y > w.pos.y)
			{
				dir.y *= -1.0;
				pos.y = w.pos.y - dim.y;
			}
			// bottom mid
			if (pos.y < w.pos.y + w.dim.y && pos.y + dim.y > w.pos.y + w.dim.y)
			{
				dir.y *= -1.0;
				pos.y = w.pos.y + w.dim.y;
			}
		}
		// mid, caller engulfs
		else if (pos.x > w.pos.x && pos.x + dim.x < w.pos.x + w.dim.x)
		{
			// top mid
			if (pos.y < w.pos.y && pos.y + dim.y > w.pos.y)
			{
				dir.y *= -1.0;
				pos.y = w.pos.y - dim.y;
			}
			// bottom mid
			else if (pos.y < w.pos.y + w.dim.y && pos.y + dim.y > w.pos.y + w.dim.y)
			{
				dir.y *= -1.0;
				pos.y = w.pos.y + w.dim.y;
			}
		}
	}
	bool MissileCollision(Missile& m)
	{
		// left
		if (pos.x < m.pos.x && pos.x + dim.x > m.pos.x)
		{
			// top left
			if (pos.y < m.pos.y && pos.y + dim.y > m.pos.y)
			{
				return true;
			}
			// mid left
			else if (pos.y > m.pos.y && pos.y + dim.y < m.pos.y + m.dim.y)
			{
				return true;
			}
			// bottom left
			else if (pos.y < m.pos.y + m.dim.y && pos.y + dim.y > m.pos.y + m.dim.y)
			{
				return true;
			}
			// caller engulfs
			else if (pos.y < m.pos.y&& pos.y + dim.y > m.pos.y + m.dim.y)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		// right
		else if (pos.x < m.pos.x + m.dim.x && pos.x + dim.x > m.pos.x + m.dim.x)
		{
			// top right
			if (pos.y < m.pos.y && pos.y + dim.y > m.pos.y)
			{
				return true;
			}
			// mid right
			else if (pos.y > m.pos.y && pos.y + dim.y < m.pos.y + m.dim.y)
			{
				return true;
			}
			// bottom right
			else if (pos.y < m.pos.y + m.dim.y && pos.y + dim.y > m.pos.y + m.dim.y)
			{
				return true;
			}
			// caller engulfs
			else if (pos.y < m.pos.y && pos.y + dim.y > m.pos.y + m.dim.y)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		// mid, argument engulfs
		else if (pos.x > m.pos.x && pos.x + dim.x < m.pos.x + m.dim.x)
		{
			// top mid
			if (pos.y < m.pos.y && pos.y + dim.y > m.pos.y)
				return true;
			// bottom mid
			else if (pos.y < m.pos.y + m.dim.y && pos.y + dim.y > m.pos.y + m.dim.y)
				return true;
			else
				return false;
		}
		// mid, caller engulfs
		else if (pos.x > m.pos.x && pos.x + dim.x < m.pos.x + m.dim.x)
		{
			// top mid
			if (pos.y < m.pos.y && pos.y + dim.y > m.pos.y)
				return true;
			// bottom mid
			else if (pos.y < m.pos.y + m.dim.y && pos.y + dim.y > m.pos.y + m.dim.y)
				return true;
			else
				return false;
		}
		else
			return false;
	}
	void Dying(double &dt)
	{
		if (timer == 0.0)
			tex_pos = V2i{ 32,0 };
		timer += dt;
		if (timer > 1.0)
		{
			state = dead;
			tex_pos = V2i{ 64,0 };
			timer = 0.0;
		}
	}
public:
	V2d pos;
	V2d dir;
	V2d dim;
	//state
	State state;
	double timer = 0.0;
	bool collided = false;
	// graphics
	Texture tex;
	V2i tex_pos{ 0,0 };
	// sounds
	Sound dying_sound;
};